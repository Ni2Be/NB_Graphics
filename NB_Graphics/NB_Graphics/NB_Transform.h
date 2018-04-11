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
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace NB
{
	class NB_Transform
	{
	public:
		//constructor
		NB_Transform(const glm::vec3& pos   = glm::vec3(),
			         const glm::vec3& rot   = glm::vec3(),
			         const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
			:
			m_pos  (pos), 
			m_rot  (rot), 
			m_scale(scale)
		{}

		//functions
		inline glm::mat4 const get_model();
		inline void      set_scale(float vector);
		
		//get/set
		glm::vec3& pos()   { return m_pos; }
		glm::vec3& rot()   { return m_rot; }
		glm::vec3& scale() { return m_scale; }

		const glm::vec3& pos()   const { return m_pos; }
		const glm::vec3& rot()   const { return m_rot; }
		const glm::vec3& scale() const { return m_scale; }
	private:
		//member
		glm::vec3 m_pos;
		glm::vec3 m_rot;
		glm::vec3 m_scale;
	};


	//TODO maybe implement static objects that don't need to be updated every time
	inline glm::mat4 const NB_Transform::get_model()
	{
		glm::mat4 pos_mat   = glm::translate(m_pos);
		glm::mat4 scale_mat = glm::scale(m_scale);

		glm::mat4 rot_x_mat = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rot_y_mat = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rot_z_mat = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));

		glm::mat4 rot_mat   = rot_z_mat * rot_y_mat * rot_x_mat;

		return pos_mat * rot_mat * scale_mat;
	}

	inline void NB_Transform::set_scale(float vector)
	{
		m_scale.x = vector;
		m_scale.y = vector;
		m_scale.z = vector;
	}
}
#endif
