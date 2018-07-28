/*
NB_Console_Handle:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_CONSOLE_HANDLE_INCLUDED
#define NB_CONSOLE_HANDLE_INCLUDED

#ifdef __linux__ 
//TODO
#elif _WIN32
#include <windows.h>
#else
//TODO
#endif

namespace NB
{
	class NB_Console_Handler
	{
#ifdef __linux__ 
		//TODO
#elif _WIN32
	public:
		enum Console_Color
		{
			BLACK       = 0,
			DARKBLUE    = FOREGROUND_BLUE,
			DARKGREEN   = FOREGROUND_GREEN,
			DARKCYAN    = FOREGROUND_GREEN | FOREGROUND_BLUE,
			DARKRED     = FOREGROUND_RED,
			DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
			DARKYELLOW  = FOREGROUND_RED | FOREGROUND_GREEN,
			DARKGRAY    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			GRAY        = FOREGROUND_INTENSITY,
			BLUE        = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
			GREEN       = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
			CYAN        = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
			RED         = FOREGROUND_INTENSITY | FOREGROUND_RED,
			MAGENTA     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
			YELLOW      = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
			WHITE       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			DEFAULT
		};
	private:
		int    default_console_color;
		HANDLE h_console;
#else
		//TODO
#endif
	public:
		static NB_Console_Handler& console()
		{
			static NB_Console_Handler static_console;
			return static_console;
		}

		void letter_color(Console_Color color);
	private:
		NB_Console_Handler();
	};
}
#endif
