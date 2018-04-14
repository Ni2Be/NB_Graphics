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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	NB::NB_Graphics::init();

	NB::NB_Window nb_window(SCR_WIDTH, SCR_HEIGHT, "NB Test");
	nb_window.background_color() = glm::vec4(1.0, 0.2, 0.2, 1.0);

	//light
	NB::NB_Directional_Light dir_light({ 0.5f, 0.5f, -0.3f });
	//NB::NB_Point_Light       point_light({ -0.2f, -0.2f, -0.2f });

	//camera
	NB::NB_Camera camera(
			glm::radians(45.0f),
			(GLfloat)1200 / (GLfloat)700,
			0.1f,
			1000.0f);
	camera.look_at(
			glm::vec3(0.0f, 0.0f, 1.5f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

	//Material
	NB::NB_Material material1(NB::NB_PEARL);
	NB::NB_Material material2(NB::NB_PEARL);
	NB::NB_Texture texture0("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/awesomeface.png");
	NB::NB_Texture texture1("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2.png");
	NB::NB_Texture texture2("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2_specular.png", NB::NB_SPECULAR);
	material1.add_texture(texture0);
	material1.add_texture(texture0);
	material2.add_texture(texture0);

	NB::NB_Material material3 = material1;
	material2 = material1;
	
	NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/nano/nanosuit.obj");
	model.transform().pos() = glm::vec3(0.0f, -0.7f, -1.0f);
	model.transform().set_scale(0.1f);

	//NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/lion/kobanB.obj");
	//model.transform().pos() = glm::vec3(0.0f, 0.2f, -1.0f);
	//model.transform().set_scale(0.35f);

	//NB::NB_Model model("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/models/turtle/Turtle_fixed.obj");
	//model.transform().pos() = glm::vec3(0.0f, -0.2f, -1.0f);
	//model.transform().rot().x = 3 * glm::half_pi<float>();
	//model.transform().set_scale(0.007f);
	//TODO don't load multiple textures for turtle

	NB::NB_Cube cube(1.0f, 1.0f, 1.0f);
	cube.transform().pos() = glm::vec3(-1.0f, 0.0f, -1.0f);

	cube.mesh().mesh().attach(material3);

	NB::NB_Cube cube2(1.0f, 1.0f, 1.0f);
	cube2.transform().pos() = glm::vec3(1.0f, 0.0f, -1.0f);

	cube2.mesh().mesh().attach(material2);

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


		float time = glfwGetTime();
		cube.transform().rot().y += 0.01 * cos(time);
		cube.transform().rot().x += 0.01 * cos(time);

		model.transform().rot().y += 0.001;


		cube.draw();
		model.draw();
	    cube2.draw();

		nb_window.update();
	}

	NB::NB_Graphics::terminate();


	char ch;
	std::cin >> ch;
	return 0;
}

