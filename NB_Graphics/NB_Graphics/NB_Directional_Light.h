/*
NB_Directional_Light:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_DIRECTIONAL_LIGHT_H_INCLUDED
#define NB_DIRECTIONAL_LIGHT_H_INCLUDED


//GLM
#include <glm/glm.hpp>

//NB
#include "NB_Light.h"

namespace NB
{
	class NB_Light;

	class NB_Directional_Light : public NB_Light
	{
	public:
		NB_Directional_Light() {}

		NB_Directional_Light(
			glm::vec3 direction, 
			glm::vec4 color             = { 1.0f, 1.0f, 1.0f, 1.0f },
			float     strength          = 1.0f,
			float     ambient_strength  = 0.00f)
			:
			NB_Light(color, 
				     strength, 
				     ambient_strength),
			m_direction(direction)
		{}

		glm::vec3& direction() { return m_direction; }
	protected:
		glm::vec3 m_direction;
	};
}
#endif
