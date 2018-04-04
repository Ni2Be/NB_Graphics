/*
NB_Test_Application:
Attention:
Purpose:
Testing

Holds the window and anything that is
displayed on it.

Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_APPLICATION_H_INCLUDED
#define NB_APPLICATION_H_INCLUDED


// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm.hpp>

// STL
#include <string>
#include <vector>
#include <random>


// NB_Lib
#include "NB_Utility.h"
#include "NB_Window.h"
#include "NB_Camera.h"
#include "NB_Material.h"
#include "NB_Test_Shader.h"
#include "NB_Shader.h"

namespace NB
{

	class NB_Test_Application
	{
	public:
		NB_Test_Application();
		~NB_Test_Application();

		void run();
	private:
		//Window
		NB_Window m_window;

		//FPS
		GLfloat m_delta_time;
		double  m_current_frame;
		double  m_last_frame;

		//Camera
		NB::NB_Camera cam1;

		//Lights
		const int                 CONST_LIGHT_COUNT = 12;
		std::vector<NB::NB_Light> m_lights;

		//Textures
		NB::NB_Texture m_texture1;
		NB::NB_Texture m_texture2;

		//Objects
		std::vector<std::vector<NB::NB_Cube>> m_flying_cubes;
		NB::NB_Cube                           m_cube_one;
		//Shader
		NB::Test::Test_Shader_Texture m_texture_shader;

		//
		void initiate();
		void application_loop();
		void calculate_new_positions(float time);
	};

}

#endif NB_DISPLAY_H_INCLUDED
