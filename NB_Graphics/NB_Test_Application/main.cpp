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

	//light
	NB::NB_Directional_Light dir_light({ 0.5f, 0.5f, 0.3f });
	//NB::NB_Point_Light       point_light({ -0.2f, -0.2f, -0.2f });

	//camera
	NB::NB_Camera camera(
			glm::radians(45.0f),
			(GLfloat)1200 / (GLfloat)700,
			0.1f,
			1000.0f);
	camera.look_at(
			glm::vec3(0.0f, 0.0f, 3.5f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

	//Material
	NB::NB_Material material1(NB::NB_PEARL);
	NB::NB_Texture texture1("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2.png");
	NB::NB_Texture texture2("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2_specular.png", NB::NB_SPECULAR);
	material1.add_texture(texture1);
	material1.add_texture(texture2);

	
	NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/nano/nanosuit.obj");
	model.transform().pos() = glm::vec3(0.0f, -0.5f, 0.0f);
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
	
	NB::NB_Cube cube(1.0f, 1.0f, 1.0f);
	cube.transform().pos() = glm::vec3(-1.0f, 0.0f, 0.0f);

	cube.mesh().mesh().attach(material1);

	NB::NB_Cube cube2(0.5f, 0.5f, 1.0f);
	cube2.transform().pos() = glm::vec3(0.0f, -1.0f, 0.0f);

	cube2.mesh().mesh().attach(material1);

	//Light
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dismin2_2(-2, 2);
	std::uniform_real_distribution<float> dis0_1(0.1, 0.9);
	std::uniform_real_distribution<float> dis1_20(1, 20);	

	NB::NB_Material material2(NB::NB_PEARL);
	NB::NB_Texture texture0("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/white.png");
	material2.add_texture(texture0);
	std::vector<NB::NB_Cube> light_cubes;
	std::vector<NB::NB_Point_Light> point_lights;
	for (int i = 0; i < 32; i++)
	{
		point_lights.push_back(
			{glm::vec3(dismin2_2(gen), dismin2_2(gen), dismin2_2(gen) + glm::pi<float>()),
			glm::vec4{ dis0_1(gen), dis0_1(gen), dis0_1(gen), 1.0f }, 0.1f });
		
		light_cubes.push_back({0.1f, 0.1f, 0.1f});
		light_cubes[i].mesh().mesh().attach(material2);
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
		//cube.transform().rot().y += 0.01 * cos(time);
		//cube.transform().rot().x += 0.01 * cos(time);

		cube.mesh().mesh().material().shininess() = 0.5f * cos(time) + 0.5f;
		std::cout << cube.mesh().mesh().material().shininess() << std::endl;

		for (auto& point_light : point_lights)
		{
			point_light.position().z += 0.04 * cos(time);
			point_light.position().x += 0.1 * (-cos(4 * time) + sin(4 * time));
			point_light.position().y += 0.1 * ( cos(4 * time) + sin(4 * time));
		}
		for (int i = 0; i < point_lights.size(); i++)
			light_cubes[i].transform().pos() = point_lights[i].position();

		//model.transform().rot().y += 0.001;

		cube.draw();
		//model.draw();
	    //cube2.draw();
		//for (auto& light_cube : light_cubes)	
		//	light_cube.draw();

		nb_window.update();
	}

	NB::NB_Graphics::terminate();


	char ch;
	std::cin >> ch;
	return 0;
}

