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
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>

namespace NB
{
	//TODO make texture catalog less stupid


	//TODO more types
	const int CONST_ENUM_COUNT_NB_Texture_Type = 4;
	enum NB_Texture_Type
	{
		NB_DIFFUSE,
		NB_SPECULAR,
		NB_NORMAL,
		NB_HEIGHT
	};

	struct NB_Pixel
	{
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
		unsigned char a = 0;

		NB_Pixel() {}
		NB_Pixel(const glm::vec4& vec, bool multiply_255 = false) { if (multiply_255){r = vec.r * 255; g = vec.g * 255; b = vec.b * 255; a = vec.a * 255; }}
		NB_Pixel(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
	};

	//typedef std::vector<std::vector<NB::NB_Pixel>> NB_Pixel_Map;
	struct NB_Pixel_Map : public std::vector<std::vector<NB::NB_Pixel>>
	{
		NB_Pixel_Map(int height, int width)
			:
			std::vector<std::vector<NB::NB_Pixel>>(height, std::vector<NB_Pixel>(width))
		{}
		NB_Pixel_Map(const std::vector<std::vector<NB::NB_Pixel>>& pixel_map)
			:
			std::vector<std::vector<NB::NB_Pixel>>(pixel_map)
		{}
		NB_Pixel_Map(std::initializer_list<std::vector<NB::NB_Pixel>> il)
			:
			std::vector<std::vector<NB::NB_Pixel>>(il)
		{}

		NB_Pixel_Map(const std::string file_path);

		void save_to_file(const std::string file_path);
	};



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
		bool   check            (std::string path);
		void   check_in         (std::string path, GLuint texture_id);
		void   check_in         (GLuint texture_id);
		int    check_out        (std::string path, GLuint texture_id);
		GLuint get_id           (std::string path);
		int    get_texture_count(GLuint texture_id) { return m_texture_id_catalog.count(texture_id); };

		const std::unordered_map<std::string, GLuint>& texture_catalog() const { return m_texture_catalog; }
		const std::unordered_multiset<GLuint>&         texture_id_catalog() const { return m_texture_id_catalog; }
	private:
		//member
		std::unordered_map<std::string, GLuint> m_texture_catalog;
		std::unordered_multiset<GLuint> m_texture_id_catalog;
	};

	class NB_Texture
	{
	public:
		NB_Texture(){}
		NB_Texture(const std::string& file_name, NB_Texture_Type type = NB_DIFFUSE);
		NB_Texture(const NB_Pixel_Map& pixel_map, NB_Texture_Type type = NB_DIFFUSE);

		//copy
		NB_Texture(const NB_Texture&);
		friend void swap(NB_Texture& lhs, NB_Texture& rhs);
		NB_Texture & operator=(const NB_Texture&);
		~NB_Texture();

		//functions
		void update(const NB_Pixel_Map& pixel_map, bool create_new_sampler = false);
		//void update(const std::string& file_name, bool create_new_sampler = false);

		NB_Pixel_Map get_pixel_map();

		//get/set
		NB_Texture_Type& type() { return m_type; }

		const GLuint&          id()        const { return m_id; }  
		const NB_Texture_Type& type()      const { return m_type; }
	private:
		GLuint          m_id;
		NB_Texture_Type m_type;
		std::string     m_path;
		int             m_width;
		int             m_height;
	};
	void swap(NB::NB_Texture& lhs, NB::NB_Texture& rhs);
}
#endif
