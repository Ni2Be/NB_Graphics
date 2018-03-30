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
#include <glm.hpp>

//
#include "NB_Mesh.h"
#include "NB_Transformer.h"
#include "NB_Material.h"

namespace NB
{
	class NB_Object
	{
	public:
		NB_Object(glm::vec4 color, NB_Material material)
			:
			m_color(color),
			m_material(material)
		{}


		NB_Object(const NB_Object& lhs);

		virtual void draw() const;


		std::vector<NB::NB_Vertex>&	vertices() { return m_vertices; }
		NB::NB_Mesh&				mesh()     { return m_mesh; }
		NB::NB_Transformer&			position() { return m_position; }
		glm::vec4&					color()    { return m_color; }
		NB::NB_Material&			material() { return m_material; }
	protected:
		std::vector<NB::NB_Vertex> m_vertices;
		NB::NB_Mesh                m_mesh;
		NB::NB_Transformer         m_position;
		glm::vec4                  m_color;
		NB::NB_Material            m_material;

	};

	class NB_Cube : public NB_Object
	{
	public:
		NB_Cube(
			glm::vec3	pos,
			glm::vec4	color,
			float		width,
			float		height,
			float		depth,
			NB_Material material)
			:
			NB_Object(color, material)
		{
			m_position.pos() = pos;

			width  /= 2;
			height /= 2;
			depth  /= 2;

			NB_Object::m_vertices =
			{
				//Front
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, +depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				//Back/
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				//Right
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				//Left/
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, +depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				//Top
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				//Bottom
				NB::NB_Vertex{ glm::vec3{ -width, -width, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, +depth }, color, glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, -width, +depth }, color, glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -width, -depth }, color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, -depth }, color, glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
			};

			NB_Object::m_mesh = new NB::NB_Mesh(NB_Object::m_vertices);
		}

		void transform(float width, float height, float depth)
		{
			width  /= 2;
			height /= 2;
			depth  /= 2;
			NB_Object::m_vertices =
			{
				//Front
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				//Back/
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				//Right
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				//Left/
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				//Top
				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, +height, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, +height, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				//Bottom
				NB::NB_Vertex{ glm::vec3{ -width, -width, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },

				NB::NB_Vertex{ glm::vec3{ -width, -width, +depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ -width, -width, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Vertex{ glm::vec3{ +width, -width, -depth }, m_color, glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f,-1.0f, 0.0f } },
			};

			//TODO implement =operator in mesh
			m_mesh = new NB::NB_Mesh(NB_Object::m_vertices);
		}

	};
}
#endif
