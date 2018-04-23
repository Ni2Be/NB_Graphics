/*
NB_OBJECT:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_MODEL_H_INCLUDED
#define NB_MODEL_H_INCLUDED

//GLEW
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>

//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//
#include "NB_Object.h"
#include "NB_Rendering_Mesh.h"

namespace NB
{
	class NB_Model : public NB_Object
	{
	public:
		NB_Model(
			const std::string& path, 
			glm::vec4          color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			:
			NB_Object(color)
		{
			this->load_model(path);
		}

		//TODO implement animation
	private:
		//member
		std::string m_path;

		//functions
		void                             load_model  (std::string path);
		void                             process_node(aiNode* node, const aiScene* scene);
		NB_Rendering_Mesh                process_mesh(aiMesh* assimp_mesh, const aiScene* scene);
		void                             fix_mesh();
		void                             default_diffuse_map();

		NB_Material                      process_material(aiMesh* assimp_mesh, const aiScene* scene);
		void                             process_texture (aiMaterial* assimp_material, aiTextureType assimp_type, NB_Material& nb_material, NB_Texture_Type nb_type);
		std::vector<NB_Rendering_Vertex> process_vertices(aiMesh* assimp_mesh, const aiScene* scene);
		std::vector<GLuint>              process_indices (aiMesh* assimp_mesh, const aiScene* scene);
	};
}
#endif
