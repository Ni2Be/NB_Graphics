/*
NB_Mesh:
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
#ifndef NB_MESH_H_INCLUDED
#define NB_MESH_H_INCLUDED

//GLM
#include <glm.hpp>

//GLEW
#include <GL/glew.h>

//STL
#include <vector>

//NB
#include "NB_Rendering_Mesh.h"

namespace NB
{
	class NB_Vertex
	{
		friend class NB_Mesh;
	public:
		NB_Vertex(const glm::vec3& pos, glm::vec3 normal = { 1, 1, 1 })
			:
			m_pos    (pos),
			m_normal (normal)
		{}
	private:
		glm::vec3 m_pos;
		glm::vec3 m_normal;
	};

	struct NB_Triangle
	{
		int p1;
		int p2;
		int p3;
	};

	class NB_Mesh
	{
	public:
		NB_Mesh(){}

		explicit NB_Mesh(const std::vector<NB_Vertex>& vertices);

		NB_Mesh(
			const std::vector<NB_Vertex>&   vertices,
			const std::vector<NB_Triangle>& triangles,
			const std::vector<glm::vec2>&   uvs);

		void setup_mesh();
		void draw();

		std::vector<NB_Vertex>&   m_vertices() { return m_vertices; }
		std::vector<NB_Triangle>& triangles()  { return m_triangles; }
		std::vector<glm::vec2>&   uvs()        { return m_uvs; }

		void calculate_normals();
	private:
		NB::NB_Rendering_Mesh    m_rendering_mesh;

		std::vector<NB_Vertex>	 m_vertices;
		std::vector<NB_Triangle> m_triangles;
		std::vector<glm::vec2>   m_uvs;

		GLuint m_EBO;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_draw_count;
	};
}
#endif