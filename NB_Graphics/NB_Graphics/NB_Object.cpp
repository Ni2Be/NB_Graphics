#include "NB_Object.h"
#include <iostream>

NB::NB_Object::NB_Object(const NB_Object& lhs)
{
	this->m_color    = lhs.m_color;
	this->m_material = lhs.m_material;
	this->m_position = lhs.m_position;
	this->m_vertices = lhs.m_vertices;
	this->m_mesh     = NB_Mesh(this->m_vertices);
	this->m_rendering_mesh = lhs.m_rendering_mesh;
	this->m_shader   = lhs.m_shader;
}

void NB::NB_Object::draw()
{
	//TODO make work
	m_shader->use();
	m_shader->update(this); 
	m_rendering_mesh.draw();
}


std::ostream& NB::operator<<(std::ostream& stream, NB_Object& object)
{
	return stream
		<< "pos:\n\tx: " << object.m_position.pos().x
		<< " y: " << object.m_position.pos().y
		<< " z: " << object.m_position.pos().z
		<< std::endl
		<< "shader id: " << object.m_shader->program()
		<< std::endl
		<< "material:\n\ttexture id: " << object.m_material.texture->id
		<< "\n\tdiffuse id: " << object.m_material.specular_map->id;
}


std::ostream& NB::operator<<(std::ostream& stream, NB_Cube& cube)
{
	return stream << static_cast<NB::NB_Object>(cube) << std::endl
		<< "w: " << cube.m_width << " h: " << cube.m_height << " d: " << cube.m_depth;
}