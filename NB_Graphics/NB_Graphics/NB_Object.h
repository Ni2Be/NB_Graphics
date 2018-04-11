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

//
#include "NB_Rendering_Mesh.h"
#include "NB_Transform.h"
namespace NB
{
	namespace Test 
	{
		class Test_Shader_Texture;
	}
	class NB_Object
	{
	public:
		NB_Object(glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) : m_color(color) {}

		NB_Object(const NB_Object& lhs);
		NB_Object(std::vector<NB_Rendering_Vertex> vertices, std::vector<unsigned int> indices)
			:
			m_rendering_mesh(vertices, indices)
		{}

		virtual void      draw();

		NB::NB_Transform& transform() { return m_transform; }
		glm::vec4&        color()     { return m_color; }

		//for debug
		friend std::ostream& operator<<(std::ostream& stream, NB_Object& object);
	//protected:
		NB::NB_Transform m_transform;
		glm::vec4        m_color;

		std::vector<NB_Rendering_Vertex> m_vertices;
		NB::NB_Rendering_Mesh            m_rendering_mesh;
	};
	std::ostream& operator<<(std::ostream& stream, NB_Object& object);

	class NB_Square : public NB_Object
	{
	public:
		NB_Square() {}
		NB_Square(float width, float height);

		float m_width;
		float m_height;
	};
	
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
