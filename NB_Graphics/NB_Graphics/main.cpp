/*

Attention:
Member varalbles of structs are just named "*name*".
Member variables of classes are named "m_*name*", getter and setter
are named "type const *name*()", and "type& *name*()".
If a function is named "void update_*name*()" the function will
set the varable and do either a validity check or to update
the variable there needs more work to be done than just update
the varable.

*/


// GLEW
//#define GLEW_STATIC
//
//#include "NB_Test_Application.h"
//
//int main()
//{
//	NB::NB_Test_Application application;
//	application.run();
//}



//GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

//STL
#include <vector>
#include <random>
#include <algorithm>
#include <thread>

//Project

#include "NB_Utility.h"
#include "NB_Display.h"
#include "NB_Utility.h"
#include "NB_Shader.h"
#include "NB_Mesh.h"
#include "NB_Texture.h"
#include "NB_Transformer.h"
#include "NB_Camera.h"
#include "NB_Object.h"
#include "NB_Light.h"
#include "NB_Material.h"
//
#include "NB_Test_Shader.h"

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis1_2(1, 2);
	std::uniform_real_distribution<float> dis0_1(0.1, 0.9);
	std::uniform_real_distribution<float> dis1_20(1, 20);

	NB::NB_Display display{ 1200, 700, "Window" };

	const int LIGHT_COUNT = 12;
	NB::Test::Test_Shader_Texture texture_shader{ LIGHT_COUNT };

	NB::NB_Texture texture1{ "../../../res/textures/container2.png" };
	NB::NB_Texture texture2{ "../../../res/textures/container2_specular.png" };

	NB::NB_Texture texture3{ "../../../res/models/lion/koban.jpg" };
	NB::NB_Texture texture4{ "../../../res/models/lion/koban.jpg" };

	//Camera
	display.cam1.look_at(
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	texture_shader.attach(display.cam1);
	//End camera

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//DIR Light
	NB::NB_Directional_Light sun = { glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.3f, -1.0f, 0.2f }, 0.1f };
	display.set_background_color(glm::vec4{ 0.02f, 0.02f, 0.02f, 1.0f });

	texture_shader.attach(sun);
	//End die light

	//Cubes
	std::vector<NB::NB_Cube> cubes
	{
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_EMERALD),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_JADE),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_OBSIDIAN),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PEARL),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBY),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_TURQUOISE),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_BRASS),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_BONZE),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_CHROME),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_COPPER),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_SILVER),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_GOLD),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_BLACK),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_CYAN),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_GREEN),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_RED),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_WHITE),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_PLASTIC_YELLOW),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_BLACK),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_CYAN),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_GREEN),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_RED),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_WHITE),
		NB::NB_Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_RUBBER_YELLOW)
	};

	for (int i = 0; i < cubes.size(); i++)
	{
		cubes[i].material().add_Texture(texture1, texture2);
		cubes[i].position().pos().x = i - cubes.size() / 2;
	}
	std::vector<std::vector<NB::NB_Cube>> ground;

	for (int i = 0; i < cubes.size(); i++)
	{
		for (auto& cube : cubes)
		{
			cube.position().pos().z = i;
			cube.position().pos().y = dis1_20(gen);
		}
		ground.push_back(cubes);
	}

	//attach to shader
	for (int i = 0; i < ground.size(); i++)
		for (int j = 0; j < ground[i].size(); j++)
			texture_shader.attach(ground[i][j]);
	//End Cubes

	//Point lights
	std::vector<NB::NB_Light_Cube*> lights;
	lights.push_back(display.light_cube_one);
	for (int i = 1; i < LIGHT_COUNT; i++)
	{
		lights.push_back(new NB::NB_Light_Cube{
			glm::vec3(dis1_20(gen), dis1_20(gen), dis1_20(gen)),
			glm::vec4{ 0.3f, 1.0f, 1.0f, 1.0f },
			0.5f, 0.5f, 0.5f,
			NB::NB_LIGHT_WHITE });
		lights[i]->change_color(glm::vec4{ dis0_1(gen), dis0_1(gen), dis0_1(gen), 1.0f });
	}
	for (int i = 0; i < lights.size(); i++)
	{
		element_shader.attach(*lights[i]);
		texture_shader.attach(*lights[i]);
		color_shader.attach(*lights[i]);
	}
	//End point lights

	//Element test
	NB::NB_Material wood
	{
		glm::vec3{ 0.24725,	0.1995,	0.0745 },
		glm::vec3{ 0.75164, 0.60648, 0.22648 },
		glm::vec3{ 0.628281, 0.555802, 0.366065 },
		0.4f,
		texture3,
		texture4
	};


	while (!glfwWindowShouldClose(&display))
	{
		glfwPollEvents();
		display.clear();

		//Cool stuff
		float time = static_cast<float>(glfwGetTime());


		for (int i = 0; i < ground.size(); i++)
		{
			for (int n = 0; n < ground[i].size(); n++)
			{
				ground[i][n].m_position().pos.y += 0.01 * cos(time);
			}
		}

		for (int i = 1; i < LIGHT_COUNT; i++)
		{
			lights[i]->move_y(0.1f * cos(time) * pow(-1, i));
			lights[i]->move_z(0.7f * cos(time) * pow(-1, i));
		}

		texture_shader.draw();
		color_shader.draw();
		display.update();
	}


	exit(EXIT_SUCCESS);
}
