#include "NB_Mesh.h"

NB::NB_Mesh::NB_Mesh(const std::vector<NB_Vertex>& vertices)
	:
	m_vertices(vertices)
{
	for (int i = 0; i < m_vertices.size(); i += 3)
		m_triangles.push_back({i, i + 1, i + 2});

	setup_mesh();
}


NB::NB_Mesh::NB_Mesh(const std::vector<NB_Vertex>&   vertices,
	                 const std::vector<NB_Triangle>& triangles,
	                 const std::vector<glm::vec2>&   uvs)
	:
	m_vertices (vertices),
	m_triangles(triangles),
	m_uvs      (uvs)
{
	setup_mesh();
}

void NB::NB_Mesh::setup_mesh()
{
	//TODO
}

void NB::NB_Mesh::draw()
{
	//TODO
}

void NB::NB_Mesh::calculate_normals()
{
	//TODO
}
