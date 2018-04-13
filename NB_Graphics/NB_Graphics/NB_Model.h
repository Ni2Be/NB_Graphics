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
			this->loadModel(path);
		}

		//TODO implement animation
	private:
		//member
		std::string m_path;
		std::vector<NB_Material> m_materials;
		
		//functions
		void              loadModel  (std::string path);
		void              process_node(aiNode* node, const aiScene* scene);
		NB_Rendering_Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	};
}
#endif
