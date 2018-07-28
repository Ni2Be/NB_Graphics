#include "NB_Utility_Test_Application.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <NB_Graphics/NB_Utility.h>

#include "NB_Test_Utility.h"

void NB::NB_Test::NB_Utility_Test_Application::run()
{
	call_back_error();
	no_call_back_error();
}


void NB::NB_Test::NB_Utility_Test_Application::call_back_error()
{
	std::stringstream call_back_error_test_ss;
	call_back_error_test_ss << std::endl << "ERROR location: \"" << "NB::Utility" << "\""
	                        << std::endl << "Error id: 65543, WGL: Driver does not support OpenGL version 99.99" 
	                        << std::endl;
	NB_Test_Runner call_back_error_test("call back error", []()
	{
		//raise error
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 99);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 99);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwCreateWindow(10, 10, "Test", NULL, NULL);

		//set back to default
		glfwDefaultWindowHints();
	}, call_back_error_test_ss);
}

void NB::NB_Test::NB_Utility_Test_Application::no_call_back_error()
{
	std::stringstream no_call_back_error_test_ss;
	NB_Test_Runner no_call_back_error_test("no call back error", []() 
	{
	//don't raise error
		glfwCreateWindow(1000, 1000, "Test", NULL, NULL);
	}, no_call_back_error_test_ss);
}