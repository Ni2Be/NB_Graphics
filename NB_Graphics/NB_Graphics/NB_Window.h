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
		NB_Window(int width, int height, std::string title);
		~NB_Window();

		inline bool is_running() const;
		inline void clear();
		inline void update();
		inline void set_title(const std::string& title);

		//only use this if you know what you're doing
		GLFWwindow* window() { return m_window; }
	private:
		//Window
		GLFWwindow* m_window;
		glm::vec4   m_background_color;
		struct NB_Window_Properties
		{
			NB_Window_Properties(int width, int height, const std::string title)
				:
				m_width (width),
				m_height(height),
				m_title (title)
			{}
			int m_width;
			int m_height;
			std::string m_title;
		};
		NB_Window_Properties m_window_properties;

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
		glClearColor(m_background_color.r, 
			         m_background_color.g, 
			         m_background_color.b, 
			         m_background_color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	inline void NB_Window::update()
	{
		//Swap buffer
		glfwSwapBuffers(this->m_window);
	}
	void NB_Window::set_title(const std::string& title)
	{
		m_window_properties.m_title = title;
		glfwSetWindowTitle(m_window, m_window_properties.m_title.c_str());
	}

	//Callbacks
	static void cb_error(int error, const char* description);
	static void cb_framebuffer_size(GLFWwindow* window, int width, int height);
	static void cb_window_size(GLFWwindow* window, int width, int height);
}
#endif
