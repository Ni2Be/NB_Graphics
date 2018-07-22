#include "NB_Test_Planet_Mesh.h"
#include <vector>

void NB::NB_Test::NB_Planet_Test_Application::start()
{
	//window
	nb_window.background_color() = glm::vec4(0.0, 0.0, 0.0, 1.0);

	//camera
	camera.update_projection(
		glm::radians(45.0f),
		(GLfloat)WIDTH / (GLfloat)HEIGHT,
		0.1f,
		1000.0f);
	camera.look_at(
		glm::vec3(0.0f, 0.0f, 2.5f),
		glm::vec3(0.0f, 0.7f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Light
	dir_light.direction() = { 0.5f, 0.5f, -0.3f };

	point_lights = {
		{
			glm::vec3(1.5f, 0.5f, 0.0f),
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f },
		{
			glm::vec3(-1.5f, 0.2f, 0.0f),
			glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f }, 1.0f },
		{
			glm::vec3(1.5f, 2.5f, 0.0f),
			glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f }, 1.0f },
		{
			glm::vec3(-0.5f, 0.8f, 0.0f),
			glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, 1.0f }
	};

	for (int i = 0; i < point_lights.size(); i++)
	{
		light_cubes.push_back(NB::NB_Cube{ 0.1f, 0.1f, 0.1f });

		//CUSTOM TEXTURE
		NB::NB_Pixel_Map pixel = { { { point_lights[i].color(), true } } };

		NB::NB_Material temp_mat1(NB::NB_COPPER);
		temp_mat1.add_texture(NB::NB_Texture(pixel)); //new owner is the material

		light_cubes[i].mesh().mesh().add(temp_mat1);
	}
	for (int i = 0; i < light_cubes.size(); i++)
		light_cubes[i].transform().pos() = point_lights[i].position();

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	setup_planet();

	event_loop();
}

void NB::NB_Test::NB_Planet_Test_Application::event_loop()
{
	// render loop
	// -----------
	while (nb_window.is_running())
	{
		NB::NB_Event_Handler::poll_events();
		nb_window.clear();


		NB::NB_Standard_Shader::shader().update_light(dir_light);
		NB::NB_Standard_Shader::shader().update_camera(camera);
		NB::NB_Standard_Shader::shader().update_light(point_lights);

		float time = glfwGetTime();

		planet.transform().rot().y -= 0.005f;

		for (auto& light_cube : light_cubes)
			light_cube.draw();
		planet.draw();

		nb_window.update();
	}
}

void NB::NB_Test::NB_Planet_Test_Application::setup_planet()
{
	NB_Rendering_Mesh&& icosahedron = generate_octahedron();
	split_octahedron(icosahedron, 3);


	NB_Pixel_Map pixel = { { { 155, 155, 155, 255 } } };
	icosahedron.add(NB_BONZE);
	icosahedron.material().add_texture(NB_Texture(pixel));

	planet.sub_meshes().push_back(icosahedron);

	planet.transform().set_scale(0.3f);
	planet.transform().pos().y = 2.0f;
	planet.calculate_normals();

}

NB::NB_Rendering_Mesh NB::NB_Test::NB_Planet_Test_Application::generate_octahedron()
{

	//Vertices
	std::vector<NB_Rendering_Vertex> vertices{
		NB_Rendering_Vertex{ { 0.0f, 0.0f, 1.0f }, { 0.00f, 0.5f } },//0
		NB_Rendering_Vertex{ { 1.0f, 0.0f, 0.0f }, { 0.25f, 0.5f } },//1
		NB_Rendering_Vertex{ { 0.0f, 0.0f,-1.0f }, { 0.50f, 0.5f } },//2
		NB_Rendering_Vertex{ {-1.0f, 0.0f, 0.0f }, { 0.75f, 0.5f } },//3
		NB_Rendering_Vertex{ { 0.0f, 0.0f, 1.0f }, { 1.00f, 0.5f } },//4
		NB_Rendering_Vertex{ { 0.0f,-1.0f, 0.0f }, { 0.50f, 0.0f } },//5
		NB_Rendering_Vertex{ { 0.0f, 1.0f, 0.0f }, { 0.50f, 1.0f } },//6
	};

	//Triangles
	std::vector<unsigned int> indices{
		0,1,6,
		0,5,1,
		1,2,6,
		1,5,2,
		2,3,6,
		2,5,3,
		3,4,6,
		3,5,4
	};

	//Identical Vertices
	std::vector<NB::NB_Rendering_Mesh::vertex_pair> identical_vertices_indices{
		{0,4}
	};

	return NB_Rendering_Mesh(vertices, indices, identical_vertices_indices);
}

void NB::NB_Test::NB_Planet_Test_Application::split_octahedron(NB::NB_Rendering_Mesh& octahedron, int split_count)
{
	std::vector<NB_Rendering_Vertex>                new_vertices;
	std::vector<unsigned int>                       new_indices;
	std::vector<NB::NB_Rendering_Mesh::vertex_pair> new_identical_vertices_indices;


	int   k = 0;
	float r = 1.0f;
	float alpha     = glm::quarter_pi<float>() / static_cast<float>(split_count);
	float beta      = glm::quarter_pi<float>() - alpha * k;
	float tan_alpha = glm::tan(alpha);

	int i = 0;
	//for (unsigned int i = 0; i < octahedron.indices().size(); i += 3)
	//{
		//triangle edges
		glm::vec3 p0 = octahedron.vertices()[octahedron.indices()[i]].pos();
		glm::vec3 p1 = octahedron.vertices()[octahedron.indices()[i + 1]].pos();
		glm::vec3 p2 = octahedron.vertices()[octahedron.indices()[i + 2]].pos();

		//split in halfs
		glm::vec3 a { (p0 + p1) / 2.0f };
		glm::vec3 b { (p1 + p2) / 2.0f };
		glm::vec3 c { (p0 + p2) / 2.0f };

		//split futher
		//for (int s = 1; s < split_count; s++)
		//{
			//p0 / a
		float new_x = r / (tan_alpha - glm::tan(glm::pi<float>() - beta));//(in this case new z)
		glm::vec3 p_k = { tan_alpha * new_x, 0.0f, new_x };
		std::cout << p_k.x << ", " << p_k.y << ", " << p_k.z << std::endl;

		k = 1;
		beta = glm::quarter_pi<float>() - alpha * k;
		new_x = r / (tan_alpha - glm::tan(glm::pi<float>() - beta));
		glm::vec3 p_k1 = { tan_alpha * new_x, 0.0f, new_x };
		std::cout << p_k1.x << ", " << p_k1.y << ", " << p_k1.z << std::endl;
		//}
	//}
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

		NB_Rendering_Vertex{ {  1.0f,  phi, 0.0f } },
		NB_Rendering_Vertex{ { -1.0f,  phi, 0.0f } },
		NB_Rendering_Vertex{ {  1.0f, -phi, 0.0f } },
		NB_Rendering_Vertex{ { -1.0f, -phi, 0.0f } },

		NB_Rendering_Vertex{ {  phi , 0.0f,  1.0f } },
		NB_Rendering_Vertex{ {  phi , 0.0f, -1.0f } },
		NB_Rendering_Vertex{ { -phi , 0.0f,  1.0f } },
		NB_Rendering_Vertex{ { -phi , 0.0f, -1.0f } }
	};

	//Triangles
	std::vector<unsigned int> indices{
		0,  5, 10,
		5, 11, 10,
		11, 7, 10,
		7,  1, 10,
		1,  0, 10,

		2,  4,  9,
		4,  8,  9,
		8,  6,  9,
		6,  3,  9,
		3,  2,  9,

		5,  4,  2,
		5,  2, 11,
		11, 2,  3,
		11, 3,  7,
		7,  3,  6,

		4,  5,  0,
		4,  0,  8,
		8,  0,  1,
		8,  1,  6,
		6,  1,  7
	};

	return NB_Rendering_Mesh(vertices, indices);
}