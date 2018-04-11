/*
NB_Mesh:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_MESH_H_INCLUDED
#define NB_MESH_H_INCLUDED

//GLM
#include <glm/glm.hpp>

//GLEW
#include <GL/glew.h>

//STL
#include <vector>

//NB
#include "NB_Texture.h"
#include "NB_Rendering_Mesh.h"
#include "NB_Material.h"

namespace NB
{
	class NB_Mesh
	{
	public:
		//constructor
		NB_Mesh() {}
		NB_Mesh(const std::vector<NB_Rendering_Vertex>& vertices);
		NB_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
			    const std::vector<unsigned int>&        indices);
		
		//functions
		void draw();
	private:
		//member
		typedef int Matrial_Id;
		typedef std::pair<NB_Rendering_Mesh, Matrial_Id> Material_Mesh;

		std::vector<Material_Mesh> m_sub_meshes;
		std::vector<NB_Material>   m_materials;

		GLuint m_EBO;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_draw_count;
	};
}
#endif