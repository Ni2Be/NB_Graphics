//TESTED

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
#include <glm/glm.hpp>

//GLEW
#include <GL/glew.h>

//STL
#include <vector>

//NB
#include "NB_Material.h"


namespace NB
{
	class NB_Rendering_Vertex
	{
		friend class NB_Rendering_Mesh;
		friend class NB_Mesh;
	public:
		//constructor
		NB_Rendering_Vertex(
			const glm::vec3& pos,
			const glm::vec3& normal = glm::vec3{ 0.0f, 0.0f, 0.0f },
			const glm::vec2& uv = glm::vec2{ 0.0f, 0.0f })
			:
			m_pos   (pos),
			m_uv    (uv),
			m_normal(normal)
		{}
	private:
		//member
		glm::vec3 m_pos;
		glm::vec2 m_uv;
		glm::vec3 m_normal;
	};

	class NB_Rendering_Mesh
	{
		friend class NB_Mesh;
	public:
		//constructor
		NB_Rendering_Mesh() {}
		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices);
		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
			              const std::vector<unsigned int>&        indices);
		//destructor
		~NB_Rendering_Mesh();
		//copy
		NB_Rendering_Mesh(const NB_Rendering_Mesh&);
		friend void swap(NB_Rendering_Mesh& lhs, NB_Rendering_Mesh& rhs);
		NB_Rendering_Mesh & operator=(const NB_Rendering_Mesh&);
		
		//functions
		void setup_mesh();
		void draw();
		void attach(NB_Material& material);

		//get/set
		NB_Material& material() { return *m_material; }
		const NB_Material& material() const { return *m_material; }
	private:
		//member
		std::vector<NB_Rendering_Vertex> m_vertices;
		std::vector<unsigned int>        m_indices;

		NB_Material* m_material;

		GLuint m_EBO;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_draw_count;
	};
	void swap(NB::NB_Rendering_Mesh& lhs, NB::NB_Rendering_Mesh& rhs);
}
#endif