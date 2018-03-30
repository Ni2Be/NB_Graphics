#include "NB_Window.h"



NB::NB_Window::NB_Window(int width, int height, std::string title)
	:
	m_window_properties(width, height, title)
{
		//set the window properties
		set_up_glfw(m_window_properties.m_width, m_window_properties.m_height, m_window_properties.m_title);

		//set the openGL settings (openGL version is set in set_up_glfw())
		set_up_glew();

		glfwSetWindowUserPointer(m_window, (void*)this);

		//set up callbacks
		glfwSetFramebufferSizeCallback(m_window, cb_framebuffer_size);
		glfwSetWindowSizeCallback(m_window, cb_window_size);
		glfwSetErrorCallback(cb_error);
}


NB::NB_Window::~NB_Window()
{
}

void NB::NB_Window::set_up_glfw(int width, int height, const std::string title)
{
	if (!glfwInit())
	{
		error_log("NB::NB_Display::NB_Display", "Failed to initiate GLFW");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (this->m_window == nullptr)
	{
		error_log("NB::NB_Display::NB_Display", "Failed to create GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->m_window);
	glfwSwapInterval(1);
}

void NB::NB_Window::set_up_glew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		error_log("NB::NB_Display::NB_Display", "Failed to initialize GLFW");
		exit(EXIT_FAILURE);
	}

	//not screen width and height but pixels to ensure proper work on high res screens
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	glViewport(0, 0, w, h);

	//z buffer
	glEnable(GL_DEPTH_TEST);

	//Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void NB::cb_framebuffer_size(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void NB::cb_error(int error, const char* description)
{
	fputs(description, stderr);
}

void NB::cb_window_size(GLFWwindow* window, int width, int height)
{
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
}
