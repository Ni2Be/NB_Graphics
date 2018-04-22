#include "NB_Model.h"
#include "NB_Utility.h"

void NB::NB_Model::load_model(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
	

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string error = import.GetErrorString();
		NB::error_log("ERROR::ASSIMP::", error);
		return;
	}
	this->m_path = path.substr(0, path.find_last_of('/'));

	m_materials.reserve((scene->mNumMaterials)*sizeof(NB_Material));//TODO understand why this is necessary

	if (!scene->mMeshes[0]->HasTangentsAndBitangents())
	{
		scene = import.ApplyPostProcessing(aiProcess_CalcTangentSpace);
	}


	this->process_node(scene->mRootNode, scene);
}

void NB::NB_Model::process_node(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++) // 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		NB_Object::m_mesh.sub_meshes().push_back(this->process_mesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->process_node(node->mChildren[i], scene);
	}
}

NB::NB_Rendering_Mesh NB::NB_Model::process_mesh(aiMesh* assimp_mesh, const aiScene* scene)
{
	NB::event_log("NB::NB_Model::process_mesh", "New Submesh\nMaterial count: "
		+ std::to_string(scene->mNumMaterials)
		+ "\nMaterial index: "
		+ std::to_string(assimp_mesh->mMaterialIndex));

	//material
	const NB::NB_Material& material = process_material(assimp_mesh, scene);
	m_materials.push_back(material);

	//verticies
	const std::vector<NB_Rendering_Vertex>& vertices = process_vertices(assimp_mesh, scene);

	//indices
	const std::vector<GLuint>& indices = process_indices(assimp_mesh, scene);

	NB_Rendering_Mesh rendering_mesh(vertices, indices);
	rendering_mesh.attach(m_materials.back());
	return rendering_mesh;
}


NB::NB_Material NB::NB_Model::process_material(aiMesh* assimp_mesh, const aiScene* scene)
{
	NB_Material material(NB::NB_PLASTIC_WHITE); //standard values if nothing is defined

	aiColor3D temp_color;
	scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, temp_color);
	if (&temp_color != nullptr)
		material.diffuse() = glm::vec3(temp_color.r, temp_color.g, temp_color.b);
	scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, temp_color);
	if (&temp_color != nullptr)
		material.specular() = glm::vec3(temp_color.r, temp_color.g, temp_color.b);
	scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, temp_color);
	if (&temp_color != nullptr)
		material.ambient() = glm::vec3(temp_color.r, temp_color.g, temp_color.b);
	
	float temp_float;
	scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_SHININESS, temp_float);
	
	//TODO warning message if not an obj file
	temp_float = temp_float / 4000.0f;//.obj files shininess 0 to 4000

	if (&temp_float != nullptr)
		material.shininess() = temp_float;

	if (assimp_mesh->mMaterialIndex >= 0)
	{
		aiMaterial *assimp_material = scene->mMaterials[assimp_mesh->mMaterialIndex];

		process_texture(assimp_material, aiTextureType_DIFFUSE, material, NB::NB_DIFFUSE);
		process_texture(assimp_material, aiTextureType_SPECULAR, material, NB::NB_SPECULAR);
		process_texture(assimp_material, aiTextureType_NORMALS, material, NB::NB_NORMAL);
		process_texture(assimp_material, aiTextureType_HEIGHT, material, NB::NB_NORMAL);//TODO hadle files correctly
	}
	return material;
}


void NB::NB_Model::process_texture(aiMaterial* assimp_matrial, aiTextureType assimp_type, NB_Material& nb_material, NB_Texture_Type nb_type)
{
	if (assimp_matrial->GetTextureCount(assimp_type) > 0)
	{
		aiString assimp_texture_path;
		assimp_matrial->GetTexture(assimp_type, (unsigned int)0, &assimp_texture_path);
		NB_Texture texture(this->m_path + "/" + assimp_texture_path.C_Str(), nb_type);
		nb_material.add_texture(texture);

		NB::event_log("NB::NB_Model::process_texture", "Texture path: "
			+ this->m_path + "/" + assimp_texture_path.C_Str()
			+ "\nTexture count: "
			+ std::to_string(assimp_matrial->GetTextureCount(assimp_type)));
	}
}

std::vector<NB::NB_Rendering_Vertex> NB::NB_Model::process_vertices(aiMesh* assimp_mesh, const aiScene* scene)
{
	std::vector<NB_Rendering_Vertex> vertices;

	if (assimp_mesh->HasTextureCoords(0))
	{
		for (GLuint i = 0; i < assimp_mesh->mNumVertices; i++)
		{
			vertices.push_back
			(
				NB::NB_Rendering_Vertex{
					glm::vec3{ assimp_mesh->mVertices[i].x        , assimp_mesh->mVertices[i].y        , assimp_mesh->mVertices[i].z },
					glm::vec3{ assimp_mesh->mNormals[i].x         , assimp_mesh->mNormals[i].y         , assimp_mesh->mNormals[i].z },
					glm::vec2{ assimp_mesh->mTextureCoords[0][i].x, assimp_mesh->mTextureCoords[0][i].y },
					glm::vec3{ assimp_mesh->mTangents->x          , assimp_mesh->mTangents->y          , assimp_mesh->mTangents->z },
					glm::vec3{ assimp_mesh->mBitangents->x        , assimp_mesh->mBitangents->y        , assimp_mesh->mBitangents->z } }
			);
		}
	}
	else
	{
		for (GLuint i = 0; i < assimp_mesh->mNumVertices; i++)
		{
			vertices.push_back
			(
				NB::NB_Rendering_Vertex{
					glm::vec3{ assimp_mesh->mVertices[i].x, assimp_mesh->mVertices[i].y, assimp_mesh->mVertices[i].z },
					glm::vec3{ assimp_mesh->mNormals[i].x , assimp_mesh->mNormals[i].y , assimp_mesh->mNormals[i].z },
					glm::vec2{ 0.0f, 0.0f },
					glm::vec3{ assimp_mesh->mTangents->x  , assimp_mesh->mTangents->y  , assimp_mesh->mTangents->z },
					glm::vec3{ assimp_mesh->mBitangents->x, assimp_mesh->mBitangents->y, assimp_mesh->mBitangents->z } }
			);
		}
	}
	return vertices;
}

std::vector<GLuint> NB::NB_Model::process_indices(aiMesh* assimp_mesh, const aiScene* scene)
{
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < assimp_mesh->mNumFaces; i++)
	{
		aiFace face = assimp_mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	return indices;
}
