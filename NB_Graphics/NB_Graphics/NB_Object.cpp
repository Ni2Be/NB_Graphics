#include "NB_Object.h"

NB::NB_Object::NB_Object(const NB_Object& lhs)
{
	this->m_color    = lhs.m_color;
	this->m_material = lhs.m_material;
	this->m_position = lhs.m_position;
	this->m_vertices = lhs.m_vertices;
	this->m_mesh     = new NB_Mesh(this->m_vertices);
}

void NB::NB_Object::draw() const
{
	m_mesh->draw();
}
