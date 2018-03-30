/*
NB_Texture:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_TEXTURE_H_INCLUDED
#define NB_TEXTURE_H_INCLUDED

//GLEW
#include <GL/glew.h>

//STL
#include <string>

namespace NB
{
	class NB_Texture
	{
	public:
		NB_Texture(const std::string& file_name);
		GLuint id;
	};
}

#endif
