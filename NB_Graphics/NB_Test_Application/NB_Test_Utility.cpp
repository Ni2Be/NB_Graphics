#include "NB_Test_Utility.h"

#include <iostream>

#include <NB_Graphics/NB_Utility.h>

NB::NB_Test::NB_Test_Runner::NB_Test_Runner(const std::string& test_name, std::function<bool()> test_function)
{
	std::cout << std::endl << "---- Test " + test_name + " ----" << std::endl;

	//raise error
	bool success = test_function();

	if (success)
	{
		NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DARKGREEN);
		std::cout << "SUCCESS!" << std::endl;
	}
	else
	{
		NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DARKRED);
		std::cout << "FAILED!" << std::endl;
	}
	NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DEFAULT);
	std::cout << "----END TEST----" << std::endl;
}

NB::NB_Test::NB_Test_Runner::NB_Test_Runner(const std::string& test_name, std::function<void()> test_function, std::stringstream& predicted_cerr_output)
{
	std::cout << std::endl << "---- Test " + test_name + " ----" << std::endl;
	
	//redirect output from std::cerr
	std::ostringstream error_stream;
	auto cerr_buff = std::cerr.rdbuf(); // save pointer to std::cerr buffer
	std::cerr.rdbuf(error_stream.rdbuf());

	//raise error
	test_function();

	//set back to default
	std::cerr.rdbuf(cerr_buff);


	std::string predicted_outcome = predicted_cerr_output.str();
	bool        success           = false;

	if (predicted_outcome == error_stream.str())
	{
		success = true;
		NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DARKGREEN);
		std::cout << "SUCCESS!" << std::endl;
	}
	else
	{
		NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DARKRED);
		std::cout << "FAILED!" << std::endl;
	}

	std::cout << "predicted outcome:\n" + predicted_outcome + "\noutcome:\n" + error_stream.str() << std::endl;
	NB::NB_Console_Handler::console().letter_color(NB_Console_Handler::DEFAULT);

	std::cout << "----END TEST----" << std::endl;
}