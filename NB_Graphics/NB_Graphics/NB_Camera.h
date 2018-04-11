/*
NB_Camera:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_CAMERA_H_INCLUDED
#define NB_CAMERA_H_INCLUDED

//GLUE
#include <GL/glew.h>

//GLM
#include <glm/gtx/transform.hpp>

//STL
#include <iostream>
#include <memory>

namespace NB
{
	class NB_Camera
	{
	public:
		NB_Camera() {}
		NB_Camera(float fov, float aspect, float z_near, float z_far);

		inline void  look_at(glm::vec3 pos, glm::vec3 front, glm::vec3 up);

		//TODO implement turn around axies
		virtual void move_forward  (float distance);
		virtual void move_backward (float distance);
		virtual void move_right    (float distance);
		virtual void move_left     (float distance);
		virtual void move_up       (float distance);
		virtual void move_down     (float distance);

		virtual void rotate(glm::vec3 roation);

		void update_front  (glm::vec3 front);
		void update_up     (glm::vec3 up);
		void update_pos    (glm::vec3 pos);
		void update_fov    (GLfloat   fov);
		void update_aspect (GLfloat   aspect);
		void update_z_far  (GLfloat   z_far);
		void aupdate_z_near(GLfloat   z_near);

		GLfloat fov()            const { return this->m_fov; }
		GLfloat aspect()         const { return this->m_aspect; }
		GLfloat z_far()          const { return this->m_z_far; }
		GLfloat z_near()         const { return this->m_z_near; }
		
		glm::mat4 projection()   const { return this->m_projection; }
		glm::mat4 view()         const { return this->m_view; }
		glm::vec3 pos()          const { return this->m_pos; }
		glm::vec3 front()        const { return this->m_front; }
		glm::vec3 up()           const { return this->m_up; }

		//for debug
		friend std::ostream& operator<<(std::ostream& stream, NB_Camera& camera);
	protected:
		GLfloat   m_fov;
		GLfloat   m_aspect;
		GLfloat   m_z_far;
		GLfloat   m_z_near;

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_pos;
		glm::vec3 m_front;
		glm::vec3 m_up;

		void update();
	};

	std::ostream& operator<<(std::ostream& stream, NB_Camera& camera);

	inline void NB_Camera::look_at(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
	{
		m_pos   = pos;
		m_front = front;
		m_up    = up;
		m_view  = glm::lookAt(m_pos, m_pos + m_front, m_up);
	}

}
#endif
