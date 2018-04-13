#include "NB_Model.h"
#include "NB_Utility.h"

void NB::NB_Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string error = import.GetErrorString();
		NB::error_log("ERROR::ASSIMP::", error);
		return;
	}
	this->m_path = path.substr(0, path.find_last_of('/'));

	m_materials.reserve((scene->mNumMaterials)*sizeof(NB_Material));//TODO understand why this is necessary
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

NB::NB_Rendering_Mesh NB::NB_Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	//material
	//TODO set right material parameters from mesh
	NB::NB_Material material(NB::NB_PEARL);

	std::cout << "\n\nNew Submesh" << std::endl;
	std::cout << "Material count: " << scene->mNumMaterials << std::endl;
	std::cout << "Material index: " << mesh->mMaterialIndex << std::endl;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

		if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString diffuse_dict;
			ai_material->GetTexture(aiTextureType_DIFFUSE, (unsigned int)0, &diffuse_dict);
			NB_Texture diffuse(this->m_path + "/" + diffuse_dict.C_Str(), NB::NB_DIFFUSE);
			material.add_texture(diffuse);

			std::cout << "Texture path: " << this->m_path + "/" + diffuse_dict.C_Str() << std::endl;
			std::cout << "Texture count: " << ai_material->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
		}
		if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			aiString specular_dict;
			ai_material->GetTexture(aiTextureType_SPECULAR, (unsigned int)0, &specular_dict);
			NB_Texture specular(this->m_path + "/" + specular_dict.C_Str(), NB::NB_SPECULAR);
			material.add_texture(specular);

			std::cout << "Texture path: " << this->m_path + "/" + specular_dict.C_Str() << std::endl;
			std::cout << "Texture count: " << ai_material->GetTextureCount(aiTextureType_SPECULAR) << std::endl;
		}
	}
	m_materials.push_back(material);

	//verticies
	std::vector<NB_Rendering_Vertex> vertices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back
			(
			NB::NB_Rendering_Vertex{
				glm::vec3{ mesh->mVertices[i].x        , mesh->mVertices[i].y        , mesh->mVertices[i].z },
				glm::vec3{ mesh->mNormals[i].x         , mesh->mNormals[i].y         , mesh->mNormals[i].z },
				glm::vec2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y } }
			);
	}
	//indices
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	NB_Rendering_Mesh rendering_mesh(vertices, indices);
	rendering_mesh.attach(m_materials.back());
	return rendering_mesh;
}

