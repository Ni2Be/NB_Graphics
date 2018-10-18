#include <iostream>
#include <string>

//glu
#include <GL/glew.h>

//glfw
#include <GLFW/glfw3.h>

//NB Test
//#include "NB_Model_Test_Application.h"
#include "NB_Planet_Test_Application.h"
//#include "NB_Utility_Test_Application.h"

//stl
#include <random>
#include <algorithm>


int main()
{
	NB::NB_Graphics::init();
	
	//NB::NB_Test::NB_Model_Test_Application model_test;
	//model_test.run();

	NB::NB_Test::NB_Planet_Test_Application planet_test;
	planet_test.run();

	//NB::NB_Test::NB_Utility_Test_Application utility_test;
	//utility_test.run();

	NB::NB_Graphics::terminate();

	char ch;
	std::cin >> ch;
	return 0;
}

