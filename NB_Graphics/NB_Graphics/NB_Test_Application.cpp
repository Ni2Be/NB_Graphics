#include "NB_Test_Application.h"
#include <iostream>


NB::NB_Test_Application::NB_Test_Application()
	:
	m_delta_time(0.0f),
	m_last_frame(0.0f),
	m_window(1200, 700, ""),
	m_texture_shader(CONST_LIGHT_COUNT)
{
	initiate();
}

NB::NB_Test_Application::~NB_Test_Application()
{
	glfwTerminate();
}

void NB::NB_Test_Application::run()
{
	application_loop();
}

void NB::NB_Test_Application::application_loop()
{
	while (m_window.is_running())
	{
		glfwPollEvents();
		m_window.clear();

		//FPS
		m_current_frame = glfwGetTime();
		m_delta_time    = static_cast<GLfloat>(m_current_frame - m_last_frame);
		m_last_frame    = m_current_frame;
		m_window.set_title(std::to_string(1 / m_delta_time));

		//Cube / Light movement
		float time = static_cast<float>(glfwGetTime());
		//calculate_new_positions(time);
		//

		//Draw
		//for (auto vec : m_flying_cubes)
		//	for(auto object : vec)
		//		object.draw();
		m_cube_one.draw();
		//

		m_window.update();
	}
}

void NB::NB_Test_Application::initiate()
{
	//Window
	m_window.properties().background_color = glm::vec4(0.41f, 1.0f, 1.0f, 1.0f);
	//

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis0_1(0.1, 0.9);
	std::uniform_real_distribution<float> dis1_20(1, 20);

	
	//Camera
	cam1 = NB_Camera(glm::radians(45.0f),
		             (GLfloat)1200 / (GLfloat)700,
		             0.1f,
		             1000.0f),
	cam1.look_at(
		glm::vec3(0.0f, 0.0f, 100.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	m_texture_shader.attach(cam1);
	//

	//DIR Light
	NB::NB_Directional_Light sun = { glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.3f, -1.0f, 0.2f }, 0.1f };
	m_texture_shader.attach(sun);
	//

	//Texture
	m_texture1 = { "../../res/textures/container2.png" };
	m_texture2 = { "../../res/textures/container2_specular.png" };
	//

	//Cube
	m_cube_one = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f, NB::NB_EMERALD };
	m_cube_one.material().add_Texture(m_texture1, m_texture2);
	m_cube_one.m_shader = &m_texture_shader;
	//
	
	//Point lights
	for (int i = 0; i < CONST_LIGHT_COUNT; i++)
	{
		m_lights.push_back(NB::NB_Light(glm::vec3(dis1_20(gen), dis1_20(gen), dis1_20(gen)),
                           NB::NB_Light_Properties( { dis0_1(gen), dis0_1(gen), dis0_1(gen), 1.0f })));
	}
	for (int i = 0; i < m_lights.size(); i++)
	{
		m_texture_shader.attach(m_lights[i]);
	}
	//
}

void NB::NB_Test_Application::calculate_new_positions(float time)
{
	for (int i = 0; i < m_flying_cubes.size(); i++)
	{
		for (int n = 0; n < m_flying_cubes[i].size(); n++)
		{
			m_flying_cubes[i][n].position().pos().y += 0.01 * cos(time);
		}
	}

	for (int i = 0; i < m_lights.size(); i++)
	{

		m_lights[i].move_y(0.1f * cos(time) * pow(-1, i));
		m_lights[i].move_z(0.7f * cos(time) * pow(-1, i));
	}
	//
}


/*
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
		cubes[i].material().add_Texture(m_texture1, m_texture2);
		cubes[i].position().pos().x = static_cast<float>(i) - cubes.size() / 2;
		cubes[i].m_shader = &m_texture_shader;
	}
	
	for (int i = 0; i < cubes.size(); i++)
	{
		for (auto& cube : cubes)
		{
			cube.position().pos().z = i;
			cube.position().pos().y = dis1_20(gen);
		}
		m_flying_cubes.push_back(cubes);
	}

*/
