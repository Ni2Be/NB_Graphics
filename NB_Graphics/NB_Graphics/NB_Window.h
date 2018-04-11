//TESTED

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
#include <glm/glm.hpp>

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
		//constructor
		NB_Window(int width, int height, std::string title);
		
		//functions
		inline bool is_running() const;
		inline void clear();
		inline void update();

		//get/set
		void        set_size (int width, int height);
		inline void set_title(const std::string& title);
		glm::vec4&  background_color() { return m_background_color; }

		GLFWwindow* window()           { return m_window; }

		const glm::vec4& background_color() const { return m_background_color; }
		int              width()  const { return m_width; }
		int              height() const { return m_height; }
	private:
		//member
		GLFWwindow* m_window;

		int         m_width;
		int         m_height;
		std::string m_title;
		glm::vec4   m_background_color;

		//functions
		void set_up_glfw(int width, int height, const std::string title);
		void set_up_glew();

		void update_window_size();
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
		m_title = title;
		glfwSetWindowTitle(m_window, m_title.c_str());
	}

	//Callbacks
	static void cb_error(int error, const char* description);
	static void cb_framebuffer_size(GLFWwindow* window, int width, int height);
	static void cb_window_size(GLFWwindow* window, int width, int height);
}
#endif
