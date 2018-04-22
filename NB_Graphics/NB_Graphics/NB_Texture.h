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

//GLM
#include <glm/glm.hpp>

//STL
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

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

	struct NB_Pixel
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

		NB_Pixel(const glm::vec4& vec) { r = vec.r * 255; g = vec.g * 255; b = vec.b * 255; a = vec.a * 255; }
		NB_Pixel(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
	};

	typedef std::vector<std::vector<NB::NB_Pixel>> NB_Pixel_Map;

	class NB_Texture_Catalog
	{
	public:
		//singeltons
		static NB_Texture_Catalog& catalog()
		{
			static NB_Texture_Catalog static_catalog;
			return static_catalog;
		}

		//functions
		//returns true if texture is new else false
		bool   check     (std::string path);
		void   registarte(std::string path, GLuint texture_id);
		GLuint get_id    (std::string path);
	private:
		//member
		std::unordered_map<std::string, GLuint> m_texture_catalog;
	};

	class NB_Texture
	{
		//TODO destructor
	public:
		NB_Texture(){}
		NB_Texture(const std::string& file_name, NB_Texture_Type type = NB_DIFFUSE);
		NB_Texture(NB_Pixel_Map pixel_map, NB_Texture_Type type = NB_DIFFUSE);


		~NB_Texture() { std::cout << " dest text "; }

		NB_Texture_Type& type() { return m_type; }

		const GLuint&          id()        const { return m_id; }  
		const std::string&     file_path() const { return m_file_path; }
		const NB_Texture_Type& type()      const { return m_type; }

	private:
		std::string     m_file_path;
		GLuint          m_id;
		NB_Texture_Type m_type;
	};
}
#endif
