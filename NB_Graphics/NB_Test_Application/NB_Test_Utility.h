#pragma once

#include <sstream>
#include <string>
#include <functional>

namespace NB
{
	namespace NB_Test
	{
		class NB_Test_Runner
		{
		public:
			/*
			runs the test_function and prints out the Test outcome
			*/
			NB_Test_Runner(const std::string& test_name, std::function<bool()> test_function);


			/*
			runs the test_function (that should raise an error printed to cerr),
			then compares it to the predicted output
			*/
			NB_Test_Runner(const std::string& test_name, std::function<void()> test_function, std::stringstream& predicted_cerr_output);
		};
	}
}