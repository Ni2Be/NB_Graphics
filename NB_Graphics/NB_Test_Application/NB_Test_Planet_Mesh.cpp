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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
	NB_Rendering_Mesh icosahedron = generate_icosahedron();

	NB_Pixel_Map pixel = { { { 155, 155, 155, 255 } } };
	icosahedron.add(NB_BONZE);
	icosahedron.material().add_texture(NB_Texture(pixel));

	planet.sub_meshes().push_back(icosahedron);

	planet.transform().set_scale(0.3f);
	planet.transform().pos().y = 2.0f;
	planet.calculate_normals();
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