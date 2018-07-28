/*
NB_Utility:
Attention:
Purpose:
Usage:
*/
#ifndef NB_UTILITY_H_INCLUDED
#define NB_UTILITY_H_INCLUDED

#define NB_PRAGMA_ONCE_SUPPORT
#ifdef _DEBUG
//#define NB_DEBUG
#endif // _DEBUG

//NB
#include "NB_Console_Handler.h"

//stl
#include <string>

// GLFW
#include <GLFW/glfw3.h>

#define NB_EVENT_LOG
#define NB_ERROR_LOG

namespace NB
{
	namespace NB_Graphics
	{
		void init();

		void terminate();
	}

	void cb_error(int error, const char* description);

	void error_log(const std::string location, 
		           const std::string error);

	void event_log(const std::string location,
				   const std::string error);

	std::string load_file_to_string(const std::string& file_name);

	void search_replace(const std::string& file_name, 
		                const std::string& search, 
		                const std::string& replace);
}
#endif
