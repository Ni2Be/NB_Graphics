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

// NB_Lib
#include "NB_Utility.h"
#include "NB_Window.h"

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

		//
		void application_loop();
	};

}

#endif NB_DISPLAY_H_INCLUDED
