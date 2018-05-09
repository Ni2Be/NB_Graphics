#include <iostream>
#include <string>

//glu
#include <GL/glew.h>

//glfw
#include <GLFW/glfw3.h>

//NB Test
#include "NB_Test_Model_Load.h"

//stl
#include <random>
#include <algorithm>
#include <thread>


int main()
{
	NB::NB_Graphics::init();

	NB::NB_Test::NB_Model_Test_Application model_test;
	model_test.start();


	NB::NB_Graphics::terminate();

	char ch;
	std::cin >> ch;
	return 0;
}

