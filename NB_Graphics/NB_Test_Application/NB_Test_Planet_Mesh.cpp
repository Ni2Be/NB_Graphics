#include "NB_Test_Planet_Mesh.h"
#include <vector>

void NB::NB_Test::NB_Planet_Test_Application::setup()
{
	NB_Rendering_Mesh&& icosahedron = generate_icosahedron();
}

NB::NB_Rendering_Mesh NB::NB_Test::NB_Planet_Test_Application::generate_icosahedron()
{
	//golden ratio
	float phi = (1.0f + std::sqrt(5.0f)) / 2.0f;

	//Vertices
	std::vector<NB_Rendering_Vertex> vertices{
		NB_Rendering_Vertex{ { 0.0f,  1.0f,  phi } },
		NB_Rendering_Vertex{ { 0.0f, -1.0f,  phi } },
		NB_Rendering_Vertex{ { 0.0f,  1.0f, -phi } },
		NB_Rendering_Vertex{ { 0.0f, -1.0f, -phi } },

		NB_Rendering_Vertex{ { 1.0f,  phi, 0.0f } },
		NB_Rendering_Vertex{ { -1.0f,  phi, 0.0f } },
		NB_Rendering_Vertex{ { 1.0f, -phi, 0.0f } },
		NB_Rendering_Vertex{ { -1.0f, -phi, 0.0f } },

		NB_Rendering_Vertex{ { phi , 0.0f,  1.0f } },
		NB_Rendering_Vertex{ { phi , 0.0f, -1.0f } },
		NB_Rendering_Vertex{ { -phi , 0.0f,  1.0f } },
		NB_Rendering_Vertex{ { -phi , 0.0f, -1.0f } }
	};

	//Triangles
	std::vector<unsigned int> indices{
		0,  5, 10,
		5, 11, 10,
		11,  7, 10,
		7,  1, 10,
		1,  0, 10,

		2,  4,  9,
		4,  8,  9,
		8,  6,  9,
		6,  3,  9,
		3,  2,  9,

		5,  4,  2,
		5,  2, 11,
		11,  2,  3,
		11,  3,  7,
		7,  3,  6,

		4,  5,  0,
		4,  0,  8,
		8,  0,  1,
		8,  1,  6,
		6,  1,  7
	};

	return NB_Rendering_Mesh(vertices, indices);
}