#include <iostream>
#include <string>

//glu
#include <GL/glew.h>

//glfw
#include <GLFW/glfw3.h>

//Test App
#include "NB_Simple_Test_Shader.h"

//NB
#include <NB_Graphics/NB_Graphics.h>
#include <NB_Graphics/NB_Window.h>
#include <NB_Graphics/NB_Rendering_Mesh.h>
#include <NB_Graphics/NB_Event_Handler.h>
#include <NB_Graphics/NB_Texture.h>
#include <NB_Graphics/NB_Illumination.h>
#include <NB_Graphics/NB_Object.h>
#include <NB_Graphics/NB_Material.h>
#include <NB_Graphics/NB_Mesh.h>
#include <NB_Graphics/NB_Standard_Shader.h>
#include <NB_Graphics/NB_Model.h>

//stl
#include <random>
#include <algorithm>
#include <thread>
// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	NB::NB_Graphics::init();

	NB::NB_Window nb_window(SCR_WIDTH, SCR_HEIGHT, "NB Test");
	nb_window.background_color() = glm::vec4(0.0, 0.0, 0.0, 1.0);


	//camera
	NB::NB_Camera camera(
		glm::radians(45.0f),
		(GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT,
		0.1f,
		1000.0f);
	camera.look_at(
		glm::vec3(0.0f, 0.0f, 2.5f),
		glm::vec3(0.0f, 0.3f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Material
	NB::NB_Material container_mat(NB::NB_PEARL);
	//NB::NB_Texture container_dif("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2.png");
	//NB::NB_Texture container_spec("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2_specular.png", NB::NB_SPECULAR);
	//container_mat.add_texture(container_dif);
	//container_mat.add_texture(container_spec);


	NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/nano/nanosuit.obj");
	model.transform().pos() = glm::vec3(0.5f, -1.2f, 0.0f);
	model.transform().set_scale(0.17f);

	//NB::NB_Model ground("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/ground/model.obj");
	//ground.transform().pos() = glm::vec3(0.0f, -1.2f, 0.0f);
	//ground.transform().rot().x = 2.5 + glm::half_pi<float>();


	//NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/lion/kobanB.obj");
	//NB::NB_Texture texture3("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/okapi-101-spec.jpg", NB::NB_SPECULAR);
	//model.transform().pos() = glm::vec3(0.0f, 0.35f, 0.0f);
	//model.transform().set_scale(0.5f);
	//model.mesh().mesh().material().add_texture(texture3);
	//model.mesh().mesh().material().shininess() = 0.9f;

	//NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/turtle/Turtle_fixed.obj");
	//model.transform().pos() = glm::vec3(0.0f, -0.2f, -1.0f);
	//model.transform().rot().x = 3 * glm::half_pi<float>();
	//model.transform().set_scale(0.007f);

	NB::NB_Cube container(1.0f, 1.0f, 1.0f);
	container.transform().pos() = glm::vec3(-1.0f, 0.0f, 0.0f);
	container.mesh().mesh().attach(container_mat);

	NB::NB_Cube cube2(0.5f, 0.5f, 1.0f);
	cube2.transform().pos() = glm::vec3(0.0f, -1.0f, 0.0f);
	container.mesh().mesh().material().shininess() = 0.01f;

	cube2.mesh().mesh().attach(container_mat);

	//Light
	NB::NB_Directional_Light dir_light({ 0.5f, 0.5f, -0.3f });

	std::vector<NB::NB_Point_Light> point_lights = {
		{
			glm::vec3(1.5f, 0.5f, 0.0f),
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f },
		{
			glm::vec3(-1.5f, 0.2f, 0.0f),
			glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f }, 1.0f },
		{
			glm::vec3(1.5f, 1.5f, 0.0f),
			glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f }, 1.0f },
		{
			glm::vec3(-0.5f, 0.8f, 0.0f),
			glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, 1.0f }
	};

	std::vector<NB::NB_Cube>     light_cubes;
	std::vector<NB::NB_Texture>  custom_textures;
	std::vector<NB::NB_Material> light_matials(4, NB::NB_PEARL);

	for (int i = 0; i < point_lights.size(); i++)
	{
		light_cubes.push_back(NB::NB_Cube{ 0.1f, 0.1f, 0.1f });

		//CUSTOM TEXTURE
		NB::NB_Pixel_Map pixel = { { {point_lights[i].color()},{point_lights[i].color()},{point_lights[i].color()} },
								   { {point_lights[i].color()},{point_lights[i].color()},{point_lights[i].color()} } ,
		                           { {point_lights[i].color()},{point_lights[i].color()},{point_lights[i].color()} } };
		custom_textures.push_back(NB::NB_Texture(pixel));
		light_matials[i].add_texture(custom_textures[i]);
		light_cubes[i].mesh().mesh().attach(light_matials[i]);
	}
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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
		camera.rotate({0.0f, -0.001, 0.0f});

		point_lights[0].position().z = cos(time);
		point_lights[1].position().y = cos(time);
		point_lights[2].position().x = cos(time);
		point_lights[3].position().z = sin(time);
		
		model.transform().rot().y -= 0.005f;

		for (int i = 0; i < light_cubes.size(); i++)
			light_cubes[i].transform().pos() = point_lights[i].position();
		for (auto light_cube : light_cubes)	
			light_cube.draw();
		model.draw();

		nb_window.update();
	}

	NB::NB_Graphics::terminate();


	char ch;
	std::cin >> ch;
	return 0;
}

