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
	//TODO more types
	enum NB_Texture_Type
	{
		NB_DIFFUSE,
		NB_SPECULAR,
		NB_NORMAL,
		NB_HEIGHT
	};

	//TODO Texture catalog ordered by filepath

	class NB_Texture
	{
	public:
		NB_Texture(){}
		NB_Texture(const std::string& file_name, NB_Texture_Type type = NB_DIFFUSE);

		NB_Texture_Type& type() { return m_type; }

		const GLuint&          id()        const { return m_id; }  
		const std::string&     file_path() const { return m_file_path; }
		const NB_Texture_Type& type()      const { return m_type; }

		//TODO name convention
		//TODO don't load from picture, use openGL to generate
		//TODO do I you really need an one pixel color generator???
		//singeltons
		static NB_Texture& WHITE()
		{
			static NB_Texture static_texture("../res/standard textures/white.png");
			return static_texture;
		}
	private:
		std::string     m_file_path;
		GLuint          m_id;
		NB_Texture_Type m_type;
	};
}
#endif
