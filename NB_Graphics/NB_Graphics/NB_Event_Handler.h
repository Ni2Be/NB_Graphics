/*
NB_Event_Handler:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_EVENT_HANDLER_H_INCLUDED
#define NB_EVENT_HANDLER_H_INCLUDED

#include <GLFW/glfw3.h>

namespace NB
{
	namespace NB_Event_Handler
	{
		static void poll_events() 
		{
			glfwPollEvents();
		}
	}
}

#endif
