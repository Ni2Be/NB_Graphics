/*
NB_Transformer:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_TRANSFORMER_H_INCLUDED
#define NB_TRANSFORMER_H_INCLUDED


//GLM
#include <glm.hpp>
#include <gtx/transform.hpp>

namespace NB
{
	class NB_Transformer
	{
	public:
		NB_Transformer(const glm::vec3& pos   = glm::vec3(),
			           const glm::vec3& rot   = glm::vec3(),
			           const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
			:
			m_pos  (pos), 
			m_rot  (rot), 
			m_scale(scale)
		{}

		inline glm::mat4 get_model() const;
		inline void      set_scale(float vector);

		glm::vec3& pos()   { return m_pos; }
		glm::vec3& rot()   { return m_rot; }
		glm::vec3& scale() { return m_scale; }
	private:
		glm::vec3 m_pos;
		glm::vec3 m_rot;
		glm::vec3 m_scale;
	};

	inline glm::mat4 NB_Transformer::get_model() const
	{
		glm::mat4 pos_mat   = glm::translate(m_pos);
		glm::mat4 scale_mat = glm::scale(m_scale);

		glm::mat4 rot_x_mat = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rot_y_mat = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rot_z_mat = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));

		glm::mat4 rot_mat   = rot_z_mat * rot_y_mat * rot_x_mat;

		return pos_mat * rot_mat * scale_mat;
	}

	inline void NB_Transformer::set_scale(float vector)
	{
		m_scale.x = vector;
		m_scale.y = vector;
		m_scale.z = vector;
	}
}
#endif
