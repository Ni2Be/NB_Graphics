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
#include "NB_Rendering_Mesh.h"
#include "NB_Transformer.h"
#include "NB_Material.h"
#include "NB_Shader.h"

namespace NB
{
	namespace Test 
	{
		class Test_Shader_Texture;
	}
	class NB_Object
	{
	public:
		NB_Object() {}
		
		NB_Object(glm::vec4 color, NB_Material material)
			:
			m_color(color),
			m_material(material)
		{
		}
		NB_Object(const NB_Object& lhs);

		virtual void draw();


		std::vector<NB::NB_Vertex>&	vertices() { return m_vertices; }
		NB::NB_Mesh&				mesh()     { return m_mesh; }
		NB::NB_Transformer&			position() { return m_position; }
		glm::vec4&					color()    { return m_color; }
		NB::NB_Material&			material() { return m_material; }

		NB::NB_Shader*              m_shader;//TODO make beautifuller

		void attach_to_shader(NB::NB_Shader& shader);
		friend std::ostream& operator<<(std::ostream& stream, NB_Object& object);
	protected:
		
		std::vector<NB::NB_Vertex> m_vertices;
		NB::NB_Mesh                m_mesh;
		NB::NB_Rendering_Mesh      m_rendering_mesh;
		NB::NB_Transformer         m_position;
		glm::vec4                  m_color;
		NB::NB_Material            m_material;
	};

	std::ostream& operator<<(std::ostream& stream, NB_Object& object);


	class NB_Cube : public NB_Object
	{
	public:
		NB_Cube(){}

		NB_Cube(
			glm::vec3	pos,
			glm::vec4	color,
			float		width,
			float		height,
			float		depth,
			NB_Material material)
			:
			NB_Object(color, material),
			m_width(width),
			m_height(height),
			m_depth(depth)
		{
			m_position.pos() = pos;

			width  /= 2;
			height /= 2;
			depth  /= 2;

			std::vector<NB::NB_Rendering_Vertex> vertices;

			vertices =
			{
				//Front
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }},
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }},
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f } },

				//Back/
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f,-1.0f } },

				//Right
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 1.0f, 0.0f, 0.0f } },

				//Left/
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ -1.0f, 0.0f, 0.0f } },

				//Top
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f, 1.0f, 0.0f } },

				//Bottom
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, +depth }, glm::vec2{ 0.0f, 0.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },

				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, +depth }, glm::vec2{ 0.0f, 1.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, -depth }, glm::vec2{ 1.0f, 1.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, -depth }, glm::vec2{ 1.0f, 0.0f }, color, glm::vec3{ 0.0f,-1.0f, 0.0f } },
			};

			m_rendering_mesh = NB_Rendering_Mesh(vertices);
		}

		float m_width;
		float m_height;
		float m_depth;
		friend std::ostream& operator<<(std::ostream& stream, NB_Cube& cube);
	};

	std::ostream& operator<<(std::ostream& stream, NB_Cube& cube);
}
#endif
