#include "NB_Texture.h"
#include "NB_Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

#include <iostream>


//TODO should store image and provide a way to manipulate it


bool NB::NB_Texture_Catalog::check(std::string path)
{
	return !m_texture_catalog.count(path);
}

void NB::NB_Texture_Catalog::check_in(std::string path, GLuint texture_id)
{
	m_texture_catalog[path] = texture_id;
	check_in(texture_id);
}

void NB::NB_Texture_Catalog::check_in(GLuint texture_id)
{
	m_texture_id_catalog.insert(texture_id);
}

int NB::NB_Texture_Catalog::check_out(std::string path, GLuint texture_id)
{
	m_texture_id_catalog.extract(texture_id);
	if (m_texture_id_catalog.count(texture_id) == 0)
		m_texture_catalog.erase(path);
	return m_texture_id_catalog.count(texture_id);
}

GLuint NB::NB_Texture_Catalog::get_id(std::string path)
{
	return m_texture_catalog[path];
}


NB::NB_Texture::NB_Texture(const std::string& file_name, NB_Texture_Type type)
	:
	m_type(type),
	m_path(file_name)
{
	//Texture isn't loaded
	if (NB_Texture_Catalog::catalog().check(file_name))
	{
		NB::event_log("NB_Texture", "loading: " + file_name);
		//load picture
		int width, height, color_channels;//TODO use color_channels

		stbi_set_flip_vertically_on_load(1);
		unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, &color_channels, 4);
		
		if (image_data == nullptr)
		{
			NB::error_log("NB::NB_Texture::NB_Texture", "Texture loading fail: " + file_name);
		}
		else
		{
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(image_data);
		}
		//registrate new texture
		NB_Texture_Catalog::catalog().check_in(file_name, this->m_id);
	}
	//texture is loaded
	else
	{
		NB::event_log("NB::NB_Texture::NB_Texture", "from texture catalog: " + file_name);
		this->m_id = NB_Texture_Catalog::catalog().get_id(file_name);
		NB_Texture_Catalog::catalog().check_in(this->m_id);
	}
}


NB::NB_Texture::NB_Texture(NB_Pixel_Map pixel_map, NB_Texture_Type type)
	:
	m_type(type),
	m_path("none")
{
	NB::event_log("NB_Texture", "create rgba image");

	if (pixel_map.size() == 0)
		error_log("NB::NB_Texture::NB_Texture", "pixel vector is empty");
	int height = pixel_map.size();
	int width  = pixel_map[0].size();
	GLubyte* image_data = (GLubyte*)(malloc(width * height * 4 * sizeof(GLubyte)));
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			int current_pixel = h * width * 4 + w * 4;
			image_data[current_pixel + 0] = pixel_map[height - 1 - h][w].r;
			image_data[current_pixel + 1] = pixel_map[height - 1 - h][w].g;
			image_data[current_pixel + 2] = pixel_map[height - 1 - h][w].b;
			image_data[current_pixel + 3] = pixel_map[height - 1 - h][w].a;
		}
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	free(image_data);

	NB::NB_Texture_Catalog::catalog().check_in(m_id);
}

NB::NB_Texture::~NB_Texture() 
{ 
	if (NB::NB_Texture_Catalog::catalog().check_out(m_path, m_id) == 0)
	{
		NB::event_log("NB::NB_Texture::~NB_Texture() ", "destroyed texture: " + std::to_string(m_id));
		glDeleteTextures(1, &m_id);
	}
}

NB::NB_Texture::NB_Texture(const NB_Texture& rhs)
	:
	m_id       (rhs.m_id),
	m_type     (rhs.m_type),
	m_path     (rhs.m_path)
{
	NB_Texture_Catalog::catalog().check_in(this->m_path, this->m_id);
}

void NB::swap(NB_Texture& lhs, NB_Texture& rhs)
{
	using std::swap;
	swap(lhs.m_id       , rhs.m_id);
	swap(lhs.m_type     , rhs.m_type);
	swap(lhs.m_path     , rhs.m_path);
}

NB::NB_Texture& NB::NB_Texture::operator=(const NB_Texture& right)
{
	NB::NB_Texture temp(right);
	NB::swap(*this, temp);
	return *this;
}