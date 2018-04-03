/*
NB_Window:
Attention:
Purpose:
Manages the GLFW Window.
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_WINDOW_H_INCLUDED
#define NB_WINDOW_H_INCLUDED


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

namespace NB
{
	class NB_Window
	{
	public:
		struct NB_Window_Properties;

		NB_Window(int width, int height, std::string title);
		~NB_Window();

		inline bool is_running() const;
		inline void clear();
		inline void update();
		inline void set_title(const std::string& title);

		NB_Window::NB_Window_Properties& properties() { return m_properties; }

		//only use this if you know what you're doing
		GLFWwindow* window() { return m_window; }
	private:
		//Window
		GLFWwindow* m_window;
		struct NB_Window_Properties
		{
			NB_Window_Properties(int width, int height, const std::string title)
				:
				width (width),
				height(height),
				title (title)
			{}
			int         width;
			int         height;
			std::string title;
			glm::vec4   background_color;
		};
		NB_Window_Properties m_properties;

		//Setup
		void set_up_glfw(int width, int height, const std::string title);
		void set_up_glew();
	};


	inline bool NB_Window::is_running() const
	{
		return !glfwWindowShouldClose(m_window);
	}

	inline void NB_Window::clear()
	{
		glClearColor(m_properties.background_color.r,
			         m_properties.background_color.g, 
			         m_properties.background_color.b, 
			         m_properties.background_color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	inline void NB_Window::update()
	{
		//Swap buffer
		glfwSwapBuffers(this->m_window);
	}

	void NB_Window::set_title(const std::string& title)
	{
		m_properties.title = title;
		glfwSetWindowTitle(m_window, m_properties.title.c_str());
	}

	//Callbacks
	static void cb_error(int error, const char* description);
	static void cb_framebuffer_size(GLFWwindow* window, int width, int height);
	static void cb_window_size(GLFWwindow* window, int width, int height);
}
#endif
