#include "NB_Camera.h"

NB::NB_Camera::NB_Camera(float fov, float aspect, float z_near, float z_far)
	:
	m_fov       (fov),
	m_aspect    (aspect),
	m_z_near    (z_near),
	m_z_far     (z_far)
{
	m_projection = glm::perspective(fov, aspect, z_near, z_far);
}

void NB::NB_Camera::update()
{
	m_view       = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
	m_projection = glm::perspective(m_fov, m_aspect, m_z_near, m_z_far);
}

void NB::NB_Camera::move_forward(float distance)
{
	this->m_camera_pos -= distance * this->m_camera_pos;
	this->update();
}

void NB::NB_Camera::move_backward(float distance)
{
	this->m_camera_pos += distance * this->m_camera_pos;
	this->update();
}

void NB::NB_Camera::move_right(float distance)
{
	this->m_camera_pos += distance * glm::normalize(glm::cross(this->m_camera_front, this->m_camera_up));
	this->update();
}

void NB::NB_Camera::move_left(float distance)
{
	this->m_camera_pos -= distance * glm::normalize(glm::cross(this->m_camera_front, this->m_camera_up));
	this->update();
}

void NB::NB_Camera::move_up(float distance)
{
	this->m_camera_pos.y += distance;
	this->update();
}

void NB::NB_Camera::move_down(float distance)
{
	this->m_camera_pos.y -= distance;
	this->update();
}

void NB::NB_Camera::update_front(glm::vec3 front)
{
	this->m_camera_front = front;
	this->update();
}

void NB::NB_Camera::update_fov(GLfloat fov)
{
	this->m_fov = fov;
	this->update();
}

std::ostream& NB::operator<<(std::ostream& stream, NB_Camera& camera)
{
	return stream
		<< "pos:\n\tx: " << camera.camera_pos().x
		<< " y: " << camera.camera_pos().y
		<< " z: " << camera.camera_pos().z
		<< std::endl
		<< "front:\n\tx: " << camera.m_camera_front.x
		<< " y: " << camera.m_camera_front.y
		<< " z: " << camera.m_camera_front.z
		<< std::endl
		<< "up:\n\tx: " << camera.m_camera_up.x
		<< " y: " << camera.m_camera_up.y
		<< " z: " << camera.m_camera_up.z
		<< std::endl
		<< "fov: " << camera.fov()
		<< std::endl
		<< "aspect: " << camera.aspect()
		<< std::endl
		<< "z_near: " << camera.z_near()
		<< std::endl
		<< "z_far: " << camera.z_far()
		<< std::endl;
}

