//TESTED

#include "NB_Object.h"
#include <iostream>
NB::NB_Object::NB_Object(const NB_Object& lhs)
{
	this->m_color    = lhs.m_color;
	this->m_transform = lhs.m_transform;
	this->m_vertices = lhs.m_vertices;
	this->m_rendering_mesh     = NB_Rendering_Mesh(lhs.m_vertices);
}

void NB::NB_Object::draw()
{
	m_rendering_mesh.draw();
}

std::ostream& NB::operator<<(std::ostream& stream, NB_Object& object)
{
	return stream
		<< "pos:\n\tx: " << object.m_transform.pos().x
		<< " y: " << object.m_transform.pos().y
		<< " z: " << object.m_transform.pos().z
		<< std::endl;
}

//SQUARE
NB::NB_Square::NB_Square(float width, float height)
	:
	NB_Object()
{
	NB_Rendering_Mesh mesh({
		NB::NB_Rendering_Vertex{ glm::vec3( 0.5f, 0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(1.0f, 1.0f) },  // top right
		NB::NB_Rendering_Vertex{ glm::vec3( 0.5f,-0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(1.0f, 0.0f) },  // bottom right
		NB::NB_Rendering_Vertex{ glm::vec3(-0.5f,-0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(0.0f, 0.0f) },  // bottom left
		NB::NB_Rendering_Vertex{ glm::vec3(-0.5f, 0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(0.0f, 1.0f) }   // top left 
		},
		{
			0,1,3,
			1,2,3
		});

	NB_Object::m_rendering_mesh = NB_Rendering_Mesh(mesh);
}

//CUBE
NB::NB_Cube::NB_Cube(
	float		width,
	float		height,
	float		depth,
	glm::vec4	color)
	:
	NB_Object(color),
	m_width(width),
	m_height(height),
	m_depth(depth)
{
	width  /= 2;
	height /= 2;
	depth  /= 2;
	
	m_vertices =
	{
				//Front
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				//Back/														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				//Right														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				//Left/														 			  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 1.0f, 0.0f } },
																										    
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec3{ -1.0f, 0.0f, 0.0f } , glm::vec2{ 1.0f, 0.0f } },
				
				//Top														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				//Bottom													 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, +depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, +depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, -depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, +depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, -depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, -depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } }
	};

	NB_Object::m_rendering_mesh = NB_Rendering_Mesh(m_vertices);
}
