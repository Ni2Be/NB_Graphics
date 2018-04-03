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
#include <gtx/transform.hpp>

//STL
#include <iostream>

namespace NB
{
	class NB_Camera
	{
	public:
		NB_Camera() {}
		NB_Camera(float fov, float aspect, float z_near, float z_far);

		inline void  look_at(glm::vec3 pos, glm::vec3 front, glm::vec3 up);

		virtual void move_forward  (float distance);
		virtual void move_backward (float distance);
		virtual void move_right    (float distance);
		virtual void move_left     (float distance);
		virtual void move_up       (float distance);
		virtual void move_down     (float distance);

		virtual void update_front(glm::vec3 front);
		void         update_fov  (GLfloat   fov);

		GLfloat fov()            const { return this->m_fov; }
		GLfloat aspect()         const { return this->m_aspect; }
		GLfloat z_far()          const { return this->m_z_far; }
		GLfloat z_near()         const { return this->m_z_near; }
		
		GLfloat& fov()            { return this->m_fov; }
		GLfloat& aspect()         { return this->m_aspect; }
		GLfloat& z_far()          { return this->m_z_far; }
		GLfloat& z_near()         { return this->m_z_near; }



		glm::mat4 projection()   const { return this->m_projection; }
		glm::mat4 view()         const { return this->m_view; }
		glm::vec3 camera_pos()   const { return this->m_camera_pos; }
		glm::vec3 camera_front() const { return this->m_camera_front; }
		glm::vec3 camera_up()    const { return this->m_camera_up; }

		friend std::ostream& operator<<(std::ostream& stream, NB_Camera& camera);
	protected:
		GLfloat   m_fov;
		GLfloat   m_aspect;
		GLfloat   m_z_far;
		GLfloat   m_z_near;

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_camera_pos;
		glm::vec3 m_camera_front;
		glm::vec3 m_camera_up;

		void update();
	};

	std::ostream& operator<<(std::ostream& stream, NB_Camera& camera);

	inline void NB_Camera::look_at(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
	{
		m_camera_pos   = pos;
		m_camera_front = front;
		m_camera_up    = up;
		m_view         = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
	}

}
#endif
