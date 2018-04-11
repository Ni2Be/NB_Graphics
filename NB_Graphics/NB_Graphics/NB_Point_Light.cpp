#include "NB_Point_Light.h"

void NB::NB_Point_Light::move_x(float delta)
{
	this->m_position.x += delta;
}

void NB::NB_Point_Light::move_y(float delta)
{
	this->m_position.y += delta;
}

void NB::NB_Point_Light::move_z(float delta)
{
	this->m_position.z += delta;
}
