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
#include <optional>

//NB
#include "NB_Material.h"


namespace NB
{
	class NB_Rendering_Vertex
	{
		friend class NB_Rendering_Mesh;
		friend class NB_Mesh;
	public:
		//constructor normal second
		NB_Rendering_Vertex(
			const glm::vec3& pos,
			const glm::vec3& normal     = glm::vec3{ 0.0f, 0.0f, 0.0f },
			const glm::vec2& uv         = glm::vec2{ 0.0f, 0.0f },
			const glm::vec3& tangent    = glm::vec3{ 0.0f, 0.0f, 0.0f },
			const glm::vec3& bi_tangent = glm::vec3{ 0.0f, 0.0f, 0.0f })
			:
			m_pos   (pos),
			m_uv    (uv),
			m_normal(normal),
			m_tangent(tangent),
			m_bi_tangent(bi_tangent)
		{}
		//constructor uv second
		NB_Rendering_Vertex(
			const glm::vec3& pos,
			const glm::vec2& uv,
			const glm::vec3& normal     = glm::vec3{ 0.0f, 0.0f, 0.0f },
			const glm::vec3& tangent    = glm::vec3{ 0.0f, 0.0f, 0.0f },
			const glm::vec3& bi_tangent = glm::vec3{ 0.0f, 0.0f, 0.0f })
			:
			m_pos   (pos),
			m_uv    (uv),
			m_normal(normal),
			m_tangent(tangent),
			m_bi_tangent(bi_tangent)
		{}
		//get / set
		glm::vec3& pos()        { return m_pos; };
		glm::vec2& uv()         { return m_uv; };
		glm::vec3& normal()     { return m_normal; };
		glm::vec3& tangent()    { return m_tangent; };
		glm::vec3& bi_tangent() { return m_bi_tangent; };
		const glm::vec3& pos()        const { return m_pos; };
		const glm::vec2& uv()         const { return m_uv; };
		const glm::vec3& normal()     const { return m_normal; };
		const glm::vec3& tangent()    const { return m_tangent; };
		const glm::vec3& bi_tangent() const { return m_bi_tangent; };
	private:
		//member
		glm::vec3 m_pos;
		glm::vec2 m_uv;
		glm::vec3 m_normal;
		glm::vec3 m_tangent;
		glm::vec3 m_bi_tangent;
	};

	class NB_Rendering_Mesh
	{
		friend class NB_Mesh;
	public:
		typedef std::pair<unsigned int, unsigned int> vertex_pair;

		//constructor
		NB_Rendering_Mesh() {}
		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices);
		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
			              const std::vector<unsigned int>&        indices);
		NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
			              const std::vector<unsigned int>&        indices,
				          const std::vector<vertex_pair>&         identical_vertices_indices);
		//destructor
		~NB_Rendering_Mesh();
		//copy
		NB_Rendering_Mesh(const NB_Rendering_Mesh&);
		friend void swap(NB_Rendering_Mesh& lhs, NB_Rendering_Mesh& rhs);
		NB_Rendering_Mesh & operator=(const NB_Rendering_Mesh&);
		
		//functions
		void setup_mesh();
		void draw();

		//will copy the material and update its pointer to that material
		void add(const NB_Material& material);
		//will save a pointer to the attached material
		void attach(NB_Material& material);

		//get/set
		NB_Material&       material()       { return *m_material; }
		const NB_Material& material() const { return *m_material; }

		//setup_mesh() needs to be called after updating the vertices
		std::vector<NB_Rendering_Vertex>&       vertices()       { return m_vertices; };
		const std::vector<NB_Rendering_Vertex>& vertices() const { return m_vertices; };

		//setup_mesh() needs to be called after updating the indices
		std::vector<unsigned int>&       indices()       { return m_indices; }
		const std::vector<unsigned int>& indices() const { return m_indices; }

		
		//to take effect calculate_normals() needs to be called after updating the identical_vertices_indices
		std::vector<vertex_pair>&       identical_vertices_indices()       { return m_identical_vertices_indices; }
		const std::vector<vertex_pair>& identical_vertices_indices() const { return m_identical_vertices_indices; }
	private:
		//member
		std::vector<NB_Rendering_Vertex>  m_vertices;
		std::vector<unsigned int>         m_indices;
		std::vector<vertex_pair>          m_identical_vertices_indices;

		NB_Material*               m_material;
		std::optional<NB_Material> m_owned_material;

		GLuint m_EBO;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_draw_count;
	};
	void swap(NB::NB_Rendering_Mesh& lhs, NB::NB_Rendering_Mesh& rhs);
}
#endif