#include "NB_Console_Handler.h"


NB::NB_Console_Handler::NB_Console_Handler()
{
#ifdef __linux__
	//TODO
#elif _WIN32
	h_console             = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(h_console, &con_info);
	default_console_color = con_info.wAttributes;
#else
	//TODO
#endif
}

void NB::NB_Console_Handler::letter_color(Console_Color color)
{
#ifdef __linux__
	//TODO
#elif _WIN32
	HANDLE ha_console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (color == NB::NB_Console_Handler::DEFAULT)
		SetConsoleTextAttribute(ha_console, default_console_color);
	else
		SetConsoleTextAttribute(ha_console, color);
#else
	//TODO
#endif
}