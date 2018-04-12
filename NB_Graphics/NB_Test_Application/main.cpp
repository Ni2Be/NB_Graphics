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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	NB::NB_Texture texture1("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2.png");
	NB::NB_Texture texture2("D:/Programmieren/NB_Graphics/NB_Graphics/NB_Test_Application/res/textures/container2_specular.png", NB::NB_SPECULAR);
	material1.add_texture(texture1);
	material1.add_texture(texture2);

	NB::NB_Cube cube(1.0f, 1.0f, 1.0f);
	cube.transform().pos() = glm::vec3(0.0f, 0.0f, -1.0f);

	NB::NB_Cube cube2(1.0f, 1.0f, 1.0f);
	cube2.transform().pos() = glm::vec3(1.0f, 0.0f, -1.0f);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	NB::NB_Mesh mesh(cube.m_rendering_mesh, material1);

	// render loop
	// -----------
	while (nb_window.is_running())
	{
		NB::NB_Event_Handler::poll_events();
		nb_window.clear();

		float time = glfwGetTime();

		cube.transform().rot().y += 0.01 * cos(time);
		cube.transform().rot().x += 0.01 * cos(time);

		NB::NB_Standard_Shader::shader().use();

		NB::NB_Standard_Shader::shader().update_dir_light(dir_light);
		NB::NB_Standard_Shader::shader().update_camera(camera);
		NB::NB_Standard_Shader::shader().update_transform(cube.transform());


		mesh.draw();

		NB::NB_Standard_Shader::shader().update_transform(cube2.transform());
	    cube2.draw();

		nb_window.update();
	}

	NB::NB_Graphics::terminate();


	char ch;
	std::cin >> ch;
	return 0;
}

