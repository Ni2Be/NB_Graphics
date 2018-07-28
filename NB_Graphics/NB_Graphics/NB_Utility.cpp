#include "NB_Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>



#ifdef NB_ERROR_LOG
//Set up Error Log
#endif

void NB::NB_Graphics::init()
{
	glfwInit();
	glfwSetErrorCallback(cb_error);
}

void NB::NB_Graphics::terminate()
{
		glfwTerminate();


}

void NB::cb_error(int error, const char* description)
{
	NB::error_log("NB::Utility", "Error id: " + std::to_string(error) + ", " + std::string(description));
}

void NB::error_log(const std::string location, const std::string error)
{
#ifdef NB_ERROR_LOG
	std::stringstream ss;
	ss << std::endl << "ERROR location: \"" << location << "\"" << std::endl << error << std::endl;
	std::cerr << ss.str();
#endif
}

void NB::event_log(const std::string location, const std::string info)
{
#ifdef NB_EVENT_LOG
	std::stringstream ss;
	ss << std::endl << "location: \"" << location << "\"" << std::endl << info << std::endl;
	std::cout << ss.str();
#endif
}

//Simple file loading
std::string NB::load_file_to_string(const std::string& file_name)
{
	std::ifstream file((file_name).c_str());

	if (!file || !file.is_open())
		error_log("NB::load_file_to_string", "Unable to load File: " + file_name);

	std::string output((std::istreambuf_iterator<char>(file)),
		               std::istreambuf_iterator<char>());
	std::string str(output);
	return str;
}

//searchs a text in a file and replaces it, "search" can contain regex commands
void NB::search_replace(const std::string& file_name, const std::string& search, const std::string& replace)
{
	std::string   content = load_file_to_string(file_name);
	std::ofstream file(file_name);

	if (!file || !file.is_open())
		error_log("NB::load_file_to_string", "Unable to load File: " + file_name);

	std::regex search_for(search);

	// write the results to an output iterator
	std::regex_replace(std::ostreambuf_iterator<char>(file),
		               begin(content), 
		               end(content), 
		               search_for, 
		               replace);
}

