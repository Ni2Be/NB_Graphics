//TESTED


#include "NB_Rendering_Mesh.h"

#include <numeric>

#include <iostream>

//TODO implement seperate Mesh class one with, one without indices
NB::NB_Rendering_Mesh::NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices)
	:
	m_vertices(vertices),
	m_indices(vertices.size())
{
	std::iota(std::begin(m_indices), std::end(m_indices), 0);
	setup_mesh();
}

NB::NB_Rendering_Mesh::NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
	                                     const std::vector<unsigned int>&        indices)
	:
	m_vertices (vertices),
	m_indices  (indices)
{
	setup_mesh();
}

NB::NB_Rendering_Mesh::NB_Rendering_Mesh(const NB_Rendering_Mesh& rhs)
	:
	NB_Rendering_Mesh(rhs.m_vertices, rhs.m_indices) //setup_mesh() is called
{
	this->m_material = rhs.m_material;
}

void NB::swap(NB_Rendering_Mesh& lhs, NB_Rendering_Mesh& rhs)
{
	using std::swap;
	swap(lhs.m_vertices  , rhs.m_vertices);
	swap(lhs.m_indices   , rhs.m_indices);
	swap(lhs.m_EBO       , rhs.m_EBO);
	swap(lhs.m_VAO       , rhs.m_VAO);
	swap(lhs.m_VBO       , rhs.m_VBO);
	swap(lhs.m_draw_count, rhs.m_draw_count);
	swap(lhs.m_material  , rhs.m_material);
}

NB::NB_Rendering_Mesh& NB::NB_Rendering_Mesh::operator=(const NB_Rendering_Mesh& right)
{
	NB::NB_Rendering_Mesh temp(right);
	NB::swap(*this, temp);
	return *this;
}

NB::NB_Rendering_Mesh::~NB_Rendering_Mesh()
{
	glDeleteVertexArrays(1, &m_VAO); 
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
}


void NB::NB_Rendering_Mesh::setup_mesh()
{
	m_draw_count = static_cast<GLuint>(m_indices.size());

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers	 (1, &m_VBO);
	glGenBuffers	 (1, &m_EBO);

	glBindVertexArray(m_VAO);

	//TODO type of the target, size of the send data, pointer to the data, usage:
	//GL_STATIC_DRAW  : the data will most likely not change at all or very rarely.
	//GL_DYNAMIC_DRAW : the data is likely to change a lot.
	//GL_STREAM_DRAW  : the data will change every time it is drawn.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &(m_vertices[0]), GL_STREAM_DRAW);
	 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);

	//index, how many, what type are the single values, normalized?, 
	//how big is one vertex, offset
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_pos));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_uv));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_bi_tangent));

	//unbinde
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void NB::NB_Rendering_Mesh::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_draw_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void NB::NB_Rendering_Mesh::attach(NB_Material& material)
{
	this->m_material = &material;
}