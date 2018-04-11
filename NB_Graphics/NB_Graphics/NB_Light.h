/*
NB_Light:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_LIGHT_H_INCLUDED
#define NB_LIGHT_H_INCLUDED


//GLM
#include <glm/glm.hpp>

namespace NB
{
	class NB_Light
	{
	public:
		glm::vec4& color()        { return m_color; }
		float& ambient_strength() { return m_ambient_strength; }
		float& strength()         { return m_strength; }
		
		const glm::vec4& color()        const { return m_color; }
		const float& ambient_strength() const { return m_ambient_strength; }
		const float& strength()         const { return m_strength; }
	protected:
		NB_Light(
			glm::vec4 color         = { 1.0f, 1.0f, 1.0f, 1.0f },
			float strength          = 1.0f,
			float ambient_strength  = 0.2f)
			:
			m_color            (color),
			m_strength         (strength),
			m_ambient_strength (ambient_strength)
		{}
		glm::vec4 m_color;

		float m_strength;
		float m_ambient_strength;
	};
}
#endif
