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
#include <memory>

namespace NB
{
	//TODO texture catalog could save pixel_map to each texture ID


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

		//constructor
		NB_Pixel() {}
		NB_Pixel(const glm::vec4& vec, bool multiply_255 = false);
		NB_Pixel(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
		
		//ostream
		friend std::ostream& operator<<(std::ostream& stream, const NB_Pixel& pixel);
	};
	std::ostream& operator<<(std::ostream& stream, const NB_Pixel& pixel);


	class NB_Pixel_Map
	{
	public:
		//constructor
		NB_Pixel_Map(){}
		NB_Pixel_Map(int height, int width)
			:
			m_pixel (height * width),
			m_height(height),
			m_width (width)
		{}
		NB_Pixel_Map(const std::initializer_list<std::initializer_list<NB::NB_Pixel>>& il);
		NB_Pixel_Map(const std::string file_path);

		//functions
		void save_file            (const std::string file_path);
		void load_file            (const std::string file_path);
		void convert_from_bit_data(GLubyte* image_data, int width, int height);
		
		//set/get
		void* get_data_pointer() { return m_pixel.data(); }
		NB_Pixel&       operator()(int height, int width)       { return m_pixel[height * m_width + width]; }
		const NB_Pixel& operator()(int height, int width) const { return m_pixel[height * m_width + width]; }
		const int height() const { return this->m_height; }
		const int width()  const { return this->m_width; }
		const void* get_data_pointer() const { return m_pixel.data(); }
		const bool is_empty()          const { return m_height == 0 || m_width == 0; }

	private:
		typedef std::vector<NB_Pixel>::iterator iterator;
		typedef std::vector<NB_Pixel>::const_iterator const_iterator;
	public:
		iterator begin() { return m_pixel.begin(); }
		iterator end()   { return m_pixel.end(); }
		const_iterator begin() const { return m_pixel.begin(); }
		const_iterator end()   const { return m_pixel.end(); }  
	private:
		std::vector<NB_Pixel> m_pixel;
		int                   m_height = 0;
		int                   m_width  = 0;
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
		int    check_out        (GLuint texture_id);

		GLuint get_id           (std::string path);
		int    get_texture_count(GLuint texture_id) { return m_texture_id_catalog.count(texture_id); };

		const std::unordered_map<std::string, GLuint>& texture_catalog() const { return m_texture_catalog; }
		const std::unordered_multiset<GLuint>&         texture_id_catalog() const { return m_texture_id_catalog; }
	private:
		//member
		std::unordered_map<std::string, GLuint> m_texture_catalog;
		std::unordered_multiset<GLuint>         m_texture_id_catalog;
	};

	class NB_Texture
	{
	public:
		NB_Texture(){}
		NB_Texture(const std::string&  file_name, NB_Texture_Type type = NB_DIFFUSE);
		NB_Texture(const NB_Pixel_Map& pixel_map, NB_Texture_Type type = NB_DIFFUSE);

		//copy
		NB_Texture(const NB_Texture&);
		friend void swap(NB_Texture& lhs, NB_Texture& rhs);
		NB_Texture & operator=(const NB_Texture&);
		~NB_Texture();
		
		//functions
		void         update(const NB_Pixel_Map& pixel_map);
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


		void create_new_sampler(const NB_Pixel_Map& pixel_map);
	};
	void swap(NB::NB_Texture& lhs, NB::NB_Texture& rhs);
}
#endif
