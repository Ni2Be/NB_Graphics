/*
NB_Light:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_POINT_LIGHT_H_INCLUDED
#define NB_POINT_LIGHT_H_INCLUDED


//GLM
#include <glm/glm.hpp>

//NB
#include "NB_Light.h"

namespace NB
{
	class NB_Light;

	class NB_Point_Light : public NB_Light
	{
	public:
		NB_Point_Light() {}

		NB_Point_Light(
			glm::vec3 position,
			glm::vec4 color             = { 1.0f, 1.0f, 1.0f, 1.0f },
			float     strength          = 1.0f,
			float     ambient_strength  = 0.2f,
			float     attenuation_const = 1.0f,
			float     attenuation_lin   = 0.09f,
			float     attenuation_quad  = 0.032f)
			:
			NB_Light           (color, 
			                    strength, 
			                    ambient_strength),
			m_attenuation_const(attenuation_const),
			m_attenuation_lin  (attenuation_lin),
			m_attenuation_quad (attenuation_quad),
			m_position         (position)
		{}

		virtual void move_x(float delta);
		virtual void move_y(float delta);
		virtual void move_z(float delta);

		glm::vec3& position() { return m_position; }

		const glm::vec3& position() const { return m_position; }
	protected:
		float m_attenuation_const;
		float m_attenuation_lin;
		float m_attenuation_quad;

		glm::vec3 m_position;
	};
}
#endif
