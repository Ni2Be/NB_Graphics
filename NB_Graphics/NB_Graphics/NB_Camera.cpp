#include "NB_Camera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
NB::NB_Camera::NB_Camera(float fov, float aspect, float z_near, float z_far)
	:
	m_fov       (fov),
	m_aspect    (aspect),
	m_z_near    (z_near),
	m_z_far     (z_far)
{
	m_projection    = glm::perspective(fov, aspect, z_near, z_far);
}

void NB::NB_Camera::update_projection(float fov, float aspect, float z_near, float z_far)
{
	m_projection = glm::perspective(fov, aspect, z_near, z_far);
}

void NB::NB_Camera::update()
{
	m_view       = glm::lookAt(m_pos, m_pos + m_front, m_up);
	m_projection = glm::perspective(m_fov, m_aspect, m_z_near, m_z_far);
}

void NB::NB_Camera::move_forward(float distance)
{
	this->m_pos   -= distance * this->m_pos;
	this->update();
}

void NB::NB_Camera::move_backward(float distance)
{
	this->m_pos += distance * this->m_pos;
	this->update();
}

void NB::NB_Camera::move_right(float distance)
{
	this->m_pos += distance * glm::normalize(glm::cross(this->m_front, this->m_up));
	this->update();
}

void NB::NB_Camera::move_left(float distance)
{
	this->m_pos -= distance * glm::normalize(glm::cross(this->m_front, this->m_up));
	this->update();
}

void NB::NB_Camera::move_up(float distance)
{
	this->m_pos.y += distance;
	this->update();
}

void NB::NB_Camera::move_down(float distance)
{
	this->m_pos.y -= distance;
	this->update();
}

void NB::NB_Camera::rotate(glm::vec3 rotation)
{
	//TODO update front, or rotate front around pos and call update
	glm::quat quaternion = glm::quat(rotation);
	this->m_view *= glm::toMat4(quaternion);
}

void NB::NB_Camera::update_front(glm::vec3 front)
{
	this->m_front = front;
	this->update();
}

void NB::NB_Camera::update_up(glm::vec3 up)
{
	this->m_up = up;
	this->update();
}

void NB::NB_Camera::update_pos(glm::vec3 pos)
{
	this->m_pos = pos;
	this->update();
}

void NB::NB_Camera::update_fov(GLfloat fov)
{
	this->m_fov = fov;
	this->update();
}

void NB::NB_Camera::update_aspect(GLfloat aspect)
{
	this->m_aspect = aspect;
	this->update();
}

void NB::NB_Camera::update_z_far(GLfloat z_far)
{
	this->m_z_far = z_far;
	this->update();
}

void NB::NB_Camera::aupdate_z_near(GLfloat z_near)
{
	this->m_z_near = z_near;
	this->update();
}

std::ostream& NB::operator<<(std::ostream& stream, NB_Camera& camera)
{
	return stream
		<< "pos:\n\tx: " << camera.pos().x
		<< " y: " << camera.pos().y
		<< " z: " << camera.pos().z
		<< std::endl
		<< "front:\n\tx: " << camera.m_front.x
		<< " y: " << camera.m_front.y
		<< " z: " << camera.m_front.z
		<< std::endl
		<< "up:\n\tx: " << camera.m_up.x
		<< " y: " << camera.m_up.y
		<< " z: " << camera.m_up.z
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

