/*
NB_OBJECT:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_OBJECT_H_INCLUDED
#define NB_OBJECT_H_INCLUDED

//GLEW
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>

//NB
#include "NB_Standard_Shader.h"
#include "NB_Rendering_Mesh.h"
#include "NB_Mesh.h"
#include "NB_Transform.h"
namespace NB
{
	class NB_Object
	{
	public:
		NB_Object(glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) : m_color(color) {}

		virtual void      draw();

		//get/set
		NB::NB_Transform& transform() { return m_transform; }
		glm::vec4&        color()     { return m_color; }
		NB_Mesh&          mesh()      { return m_mesh; }
		
		const NB::NB_Transform& transform() const { return m_transform; }
		const glm::vec4&        color()     const { return m_color; }
		const NB_Mesh&          mesh()      const { return m_mesh; }

		//for debug
		friend std::ostream& operator<<(std::ostream& stream, NB_Object& object);
	protected:
		NB::NB_Transform m_transform;
		glm::vec4        m_color;
		NB::NB_Mesh      m_mesh;

	};
	std::ostream& operator<<(std::ostream& stream, NB_Object& object);

	//class NB_Square : public NB_Object
	//{
	//public:
	//	NB_Square() {}
	//	NB_Square(float width, float height);

	//	float m_width;
	//	float m_height;
	//};
	
	class NB_Cube : public NB_Object
	{
	public:
		NB_Cube(){}

		NB_Cube(
			float		width,
			float		height,
			float		depth,
			glm::vec4	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		float m_width;
		float m_height;
		float m_depth;

	};
}
#endif
