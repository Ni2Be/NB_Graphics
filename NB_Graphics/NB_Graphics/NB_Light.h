/*
NB_Light:
Attention:
Purpose:
Usage:
*/

#include "NB_Utility.h"
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_LIGHT_H_INCLUDED
#define NB_LIGHT_H_INCLUDED


//GLM
#include <glm.hpp>

namespace NB
{
	struct NB_Light_Properties
	{
		NB_Light_Properties(glm::vec4 color         = { 1.0f, 1.0f, 1.0f, 1.0f },
			                float strength          = 1.0f,
			                float ambient_strength  = 0.2f,
			                float attenuation_const = 1.0f,
			                float attenuation_lin   = 0.09f,
			                float attenuation_quad  = 0.032f)
			:
			color            (color),
			strength         (strength),
			ambient_strength (ambient_strength),
			attenuation_const(attenuation_const),
			attenuation_lin  (attenuation_lin),
			attenuation_quad (attenuation_quad) 
		{}

		glm::vec4 color;

		float strength;
		float ambient_strength;
		float attenuation_const;
		float attenuation_lin;
		float attenuation_quad;
	};

	class NB_Light
	{
	public:
		virtual void move_x(float delta);
		virtual void move_y(float delta);
		virtual void move_z(float delta);

		glm::vec3&           position()   { return m_position; }
		NB_Light_Properties& properties() { return m_properties; }
	
		NB_Light(glm::vec3           position,
			     NB_Light_Properties properties = NB_Light_Properties())
			:
			m_position  (position),
			m_properties(properties) 
		{}
	protected:
		glm::vec3           m_position;
		NB_Light_Properties m_properties;
	};

	class NB_Directional_Light
	{
	public:
		NB_Directional_Light(){}

		NB_Directional_Light(glm::vec3 color,
			                 glm::vec3 direction,
			                 float     strength)
			:
			m_color(color),
			m_direction(direction),
			m_strength(strength)
		{}


		glm::vec3& color()     { return m_color; }
		glm::vec3& direction() { return m_direction; }
		float&     strength()  { return m_strength; }
	protected:
		glm::vec3 m_color;
		glm::vec3 m_direction;
		float     m_strength;
	};

	


	/*const NB_Light_Properties NB_LIGHT_WHITE
	{
		glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
		1.0f,
		0.2f,
		1.0f,
		0.2f,
		0.1f
	};*/
}
#endif
