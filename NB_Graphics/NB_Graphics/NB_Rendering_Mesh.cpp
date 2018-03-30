#include "NB_Rendering_Mesh.h"



NB::NB_Rendering_Mesh::NB_Rendering_Mesh(const std::vector<NB_Rendering_Vertex>& vertices,
	                                     const std::vector<unsigned int>&        indices)
	:
	m_vertices (vertices),
	m_indices  (indices)
{
	setup_mesh();
}

NB::NB_Rendering_Mesh::~NB_Rendering_Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
}


void NB::NB_Rendering_Mesh::setup_mesh()
{
	m_draw_count = static_cast<GLuint>(m_indices.size());

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers	 (1, &m_VBO);
	glGenBuffers	 (1, &m_EBO);

	glBindVertexArray(m_VAO);

	//type of the target, size of the send data, pointer to the data, usage:
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
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_uv));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		sizeof(NB_Rendering_Vertex),
		(GLvoid*)offsetof(NB_Rendering_Vertex, m_normal));

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
