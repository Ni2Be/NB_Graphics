#include "NB_Object.h"
#include <iostream>

void NB::NB_Object::draw()
{
	//TODO could be better if mesh draws with its own transfrom relative to 
	//the transfrom of the object
	m_mesh.transform() = m_transform;
	m_mesh.draw();
}

std::ostream& NB::operator<<(std::ostream& stream, const NB_Object& object)
{
	return stream
		<< "pos:\n\tx: " << object.m_transform.pos().x
		<< " y: " << object.m_transform.pos().y
		<< " z: " << object.m_transform.pos().z
		<< std::endl;
}
//
////SQUARE
//NB::NB_Square::NB_Square(float width, float height)
//	:
//	NB_Object()
//{
//	NB_Rendering_Mesh mesh({
//		NB::NB_Rendering_Vertex{ glm::vec3( 0.5f, 0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(1.0f, 1.0f) },  // top right
//		NB::NB_Rendering_Vertex{ glm::vec3( 0.5f,-0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(1.0f, 0.0f) },  // bottom right
//		NB::NB_Rendering_Vertex{ glm::vec3(-0.5f,-0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(0.0f, 0.0f) },  // bottom left
//		NB::NB_Rendering_Vertex{ glm::vec3(-0.5f, 0.5f, -1.0f), glm::vec3(0.0f,0.0f,1.0f) , glm::vec2(0.0f, 1.0f) }   // top left 
//		},
//		{
//			0,1,3,
//			1,2,3
//		});
//
//	NB_Object::m_mesh = NB_Mesh(mesh);
//}

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

	//TODO add bi/tangents 
	NB_Rendering_Mesh mesh({
				//Front
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
				
				//Back/														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 0.0f, 0.0f,-1.0f }, glm::vec2{ 1.0f, 1.0f } },
				
				//Right														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, +depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -height, -depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				
				//Left/														 			  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ -1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, +depth }, glm::vec3{ -1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -height, -depth }, glm::vec3{ -1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ -1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				
				//Top														 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, +depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, +depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, +height, -depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, +height, -depth }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },
				
				//Bottom													 				  
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, +depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, +depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ +width, -width, -depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },
				NB::NB_Rendering_Vertex{ glm::vec3{ -width, -width, -depth } , glm::vec3{ 0.0f,-1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } }
		},
		{
			//Front
			 0,  1,  2,
			 0,  3,  2,
			//Back
			 4,  5,  6,
			 4,  7,  6,
			//Right
			 8,  9, 10,
			 8, 11, 10,
			//Left
			12, 13, 14,
			12, 15, 14,
			//Top
			16, 17, 18,
			16, 19, 18,
			//Bottom
			20, 21, 22,
			20, 23, 22
		});

	NB_Object::m_mesh = NB_Mesh(mesh);
}
