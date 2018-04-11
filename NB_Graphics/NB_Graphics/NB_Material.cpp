#include "NB_Material.h"

void NB::NB_Material::add_texture(NB_Texture& texture)
{
	if (texture.type()       == NB_DIFFUSE)
		this->m_diffuse_map  = texture;
	else if (texture.type()  == NB_SPECULAR)
		this->m_specular_map = texture;
	else if (texture.type()  == NB_NORMAL)
		this->m_normal_map   = texture;
	else if (texture.type()  == NB_HEIGHT)
		this->m_height_map   = texture;
}