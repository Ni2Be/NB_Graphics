/*
NB_Rendering_Mesh:
Attention:
Purpose:
NB_Mesh and NB_Vertex should provide and easy use
to manipulate Meshes. They provide abstract usage of uvs and triangles.

NB_Rendering_Mesh and NB_Rendering_Vertex are the real
data structures that can be drawn by the openGL rendering engine
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_RENDERING_MESH_H_INCLUDED
#define NB_RENDERING_MESH_H_INCLUDED

//GLM
#include <glm.hpp>

//GLEW
#include <GL/glew.h>

//STL
#include <vector>

namespace NB
{
	class NB_Vertex;
	class NB_Mesh;

	class NB_Rendering_Vertex
	{
		friend class NB_Rendering_Mesh;
		friend class NB_Mesh;
	private:
		NB_Rendering_Vertex(const glm::vec3& pos,
			                const glm::vec2& uv,
			                const glm::vec4& color  = glm::vec4{ 1.0f,  1.0f, 1.0f, 1.0f },
			                const glm::vec3& normal = glm::vec3{ 1.0f, 1.0f, 1.0f })
			:
			m_pos   (pos),
			m_uv    (uv),
			m_color (color),
			m_normal(normal)
		{}

		glm::vec3 m_pos;
		glm::vec2 m_uv;
		glm::vec4 m_color;
		glm::vec3 m_normal;
	};

	class NB_Rendering_Mesh
	{
		friend class NB_Mesh;
	private:
		NB_Rendering_Mesh(){}

		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
			              const std::vector<unsigned int>&        indices);

		~NB_Rendering_Mesh();

		void setup_mesh();
		void draw();

		std::vector<NB_Rendering_Vertex> m_vertices;
		std::vector<unsigned int>        m_indices;

		GLuint m_EBO;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_draw_count;
	};
}
#endif