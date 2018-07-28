#include "NB_Model_Test_Application.h"


NB::NB_Test::NB_Model_Test_Application::NB_Model_Test_Application()
	:
	nb_window(SCR_WIDTH, HEIGHT, "NB Test")
{}

void NB::NB_Test::NB_Model_Test_Application::run()
{
	//window
	nb_window.background_color() = glm::vec4(0.0, 0.0, 0.0, 1.0);

	//camera
	camera.update_projection(
		glm::radians(45.0f),
		(GLfloat)SCR_WIDTH / (GLfloat)HEIGHT,
		0.1f,
		1000.0f);
	camera.look_at(
		glm::vec3(0.0f, 0.0f, 2.5f),
		glm::vec3(0.0f, 0.7f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Model
	model.load_model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/nano/nanosuit.obj");
	model.transform().pos() = glm::vec3(0.5f, -0.0f, 0.0f);
	model.transform().set_scale(0.14f);

	//model.load_model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/lion/kobanB.obj");
	//NB::NB_Texture texture3("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/okapi-101-spec.jpg", NB::NB_SPECULAR);
	//model.transform().pos() = glm::vec3(0.0f, 1.35f, 0.0f);
	//model.transform().set_scale(0.5f);
	//model.mesh().mesh().material().add_texture(texture3);
	//model.mesh().mesh().material().shininess() = 0.9f;

	//model.load_model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/turtle/Turtle_fixed.obj");
	//model.transform().pos() = glm::vec3(0.0f, 1.2f, -1.0f);
	//model.transform().rot().x = 3 * glm::half_pi<float>();
	//model.transform().set_scale(0.007f);
	
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

	for (auto& p : NB::NB_Texture_Catalog::catalog().texture_catalog())
		std::cout << "Path: " << p.first << std::endl;
	std::cout << "\npath count: " << NB::NB_Texture_Catalog::catalog().texture_catalog().size() << std::endl;
	std::cout << "\ntex count: " << NB::NB_Texture_Catalog::catalog().texture_id_catalog().size() << std::endl;

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
	event_loop();
}

void NB::NB_Test::NB_Model_Test_Application::event_loop()
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
		camera.rotate({ 0.0f, -0.001, 0.0f });

		
		point_lights[0].position().z = cos(time);
		point_lights[1].position().y = cos(time);
		point_lights[2].position().x = cos(time);
		point_lights[3].position().z = sin(time);

		model.transform().rot().y -= 0.005f;

		for (int i = 0; i < light_cubes.size(); i++)
			light_cubes[i].transform().pos() = point_lights[i].position();

		for (auto& light_cube : light_cubes)
			light_cube.draw();
		model.draw();

		nb_window.update();
	}
}
