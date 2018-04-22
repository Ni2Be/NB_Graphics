#include "NB_Material.h"
#include <iostream>


NB::NB_Material::NB_Material(const NB_Material& rhs)
	:
	m_ambient			(rhs.m_ambient),
	m_diffuse			(rhs.m_diffuse),
	m_specular			(rhs.m_specular),
	m_shininess			(rhs.m_shininess),
	m_shininess_exponent(rhs.m_shininess_exponent),
	m_strength			(rhs.m_strength),
	m_ambient_strength	(rhs.m_ambient_strength),
	m_diffuse_map		(rhs.m_diffuse_map),
	m_specular_map		(rhs.m_specular_map),
	m_normal_map		(rhs.m_normal_map),
	m_height_map		(rhs.m_height_map),
	m_owned_diffuse_map	(rhs.m_owned_diffuse_map),
	m_owned_specular_map(rhs.m_owned_specular_map),
	m_owned_normal_map  (rhs.m_owned_normal_map),
	m_owned_height_map  (rhs.m_owned_height_map),
	m_has_diffuse_map	(rhs.m_has_diffuse_map),
	m_has_specular_map	(rhs.m_has_specular_map),
	m_has_normal_map	(rhs.m_has_normal_map),
	m_has_height_map    (rhs.m_has_height_map)
{
	//set the new pointer locations
	if (rhs.m_owned_diffuse_map.has_value())
		m_diffuse_map  = &m_owned_diffuse_map.value();
	if (rhs.m_owned_specular_map.has_value())
		m_specular_map = &m_owned_specular_map.value();
	if (rhs.m_owned_normal_map.has_value())
		m_normal_map   = &m_owned_normal_map.value();
	if (rhs.m_owned_height_map.has_value())
		m_height_map   = &m_owned_height_map.value();;
}

void NB::swap(NB_Material& lhs, NB_Material& rhs)
{
	using std::swap;
	swap(lhs.m_ambient			 ,rhs.m_ambient);
	swap(lhs.m_diffuse			 ,rhs.m_diffuse);
	swap(lhs.m_specular			 ,rhs.m_specular);
	swap(lhs.m_shininess		 ,rhs.m_shininess);
	swap(lhs.m_shininess_exponent,rhs.m_shininess_exponent);
	swap(lhs.m_strength			 ,rhs.m_strength);
	swap(lhs.m_ambient_strength	 ,rhs.m_ambient_strength);
	swap(lhs.m_diffuse_map		 ,rhs.m_diffuse_map);
	swap(lhs.m_specular_map		 ,rhs.m_specular_map);
	swap(lhs.m_normal_map		 ,rhs.m_normal_map);
	swap(lhs.m_height_map		 ,rhs.m_height_map);
	swap(lhs.m_has_diffuse_map	 ,rhs.m_has_diffuse_map);
	swap(lhs.m_has_specular_map	 ,rhs.m_has_specular_map);
	swap(lhs.m_has_normal_map	 ,rhs.m_has_normal_map);
	swap(lhs.m_has_height_map    ,rhs.m_has_height_map);
}

NB::NB_Material& NB::NB_Material::operator=(const NB_Material& right)
{
	NB::NB_Material temp(right);
	NB::swap(*this, temp);
	return *this;
}


void NB::NB_Material::attach_texture(NB_Texture& texture)
{
	if (texture.type()           == NB_DIFFUSE)
	{
		this->m_diffuse_map      = &texture;
		this->m_has_diffuse_map  = true;
		m_owned_diffuse_map.reset();
	}
	else if (texture.type()      == NB_SPECULAR)
	{
		this->m_specular_map     = &texture;
		this->m_has_specular_map = true; 
		m_owned_specular_map.reset();
	}
	else if (texture.type()      == NB_NORMAL)
	{
		this->m_normal_map       = &texture;
		this->m_has_normal_map   = true;
		m_owned_normal_map.reset();
	}
	else if (texture.type()      == NB_HEIGHT)
	{
		this->m_height_map       = &texture;
		this->m_has_height_map   = true;
		m_owned_height_map.reset();
	}
}


void NB::NB_Material::add_texture(const NB_Texture& texture)
{
	if (texture.type()           == NB_DIFFUSE)
	{
		this->m_owned_diffuse_map = NB_Texture(texture);
		this->m_diffuse_map       = &m_owned_diffuse_map.value();
		this->m_has_diffuse_map   = true;
	}
	else if (texture.type()      == NB_SPECULAR)
	{
		this->m_owned_specular_map = NB_Texture(texture);
		this->m_specular_map       = &m_owned_specular_map.value();
		this->m_has_specular_map   = true;
	}
	else if (texture.type()      == NB_NORMAL)
	{
		this->m_owned_normal_map = NB_Texture(texture);
		this->m_normal_map       = &m_owned_normal_map.value();
		this->m_has_normal_map   = true;
	}
	else if (texture.type()      == NB_HEIGHT)
	{
		this->m_owned_height_map = NB_Texture(texture);
		this->m_height_map       = &m_owned_height_map.value();
		this->m_has_height_map   = true;
	}
}