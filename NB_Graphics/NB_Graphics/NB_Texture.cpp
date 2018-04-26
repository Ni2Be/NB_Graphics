#include "NB_Texture.h"
#include "NB_Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb-master/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb-master/stb_image_write.h>

#include <iostream>


//TODO use smartpointer
//TODO should store image and provide a way to manipulate it


//NB_PIXEL_MAP
NB::NB_Pixel_Map::NB_Pixel_Map(const std::string file_path)
{
	NB::event_log("NB::NB_Pixel_Map::NB_Pixel_Map", "loading: " + file_path);
	int gl_width, gl_height, color_channels;
	//stbi_set_flip_vertically_on_load(1);
	std::unique_ptr<GLubyte, decltype(stbi_image_free)*> image_data(reinterpret_cast<GLubyte*>(stbi_load(file_path.c_str(), &gl_width, &gl_height, &color_channels, 4)), stbi_image_free);

	if (image_data.get() == nullptr)
	{
		NB::error_log("NB::NB_Pixel_Map::NB_Pixel_Map", "Texture loading fail: " + file_path);
	}

	this->convert_from_gl_data(image_data.get(), gl_width, gl_height);
}

void NB::NB_Pixel_Map::save_to_file(const std::string file_path)
{
	NB::event_log("NB::NB_Pixel_Map::save_to_file", "saving to: " + file_path + ".bmp");
	auto&& image_data = convert_to_gl_data();
	stbi_flip_vertically_on_write(1);
	stbi_write_bmp((file_path + ".bmp").c_str(), this->width(), this->height(), STBI_rgb_alpha, image_data.get());
}

std::unique_ptr<GLubyte, decltype(free)*> NB::NB_Pixel_Map::convert_to_gl_data() const
{
	std::unique_ptr<GLubyte, decltype(free)*> image_data(reinterpret_cast<GLubyte*>(malloc(this->width() * this->height() * 4 * sizeof(GLubyte))), free);
	for (int h = 0; h < this->height(); h++)
	{
		for (int w = 0; w < this->width(); w++)
		{
			int current_pixel = h * this->width() * 4 + w * 4;
			image_data.get()[current_pixel + 0] = (*this)[this->height() - 1 - h][w].r;
			image_data.get()[current_pixel + 1] = (*this)[this->height() - 1 - h][w].g;
			image_data.get()[current_pixel + 2] = (*this)[this->height() - 1 - h][w].b;
			image_data.get()[current_pixel + 3] = (*this)[this->height() - 1 - h][w].a;
		}
	}
	return image_data;
}

void NB::NB_Pixel_Map::convert_from_gl_data(GLubyte* image_data, int width, int height)
{	
	NB_Pixel_Map temp(width, height);
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			int current_pixel = h * width * 4 + w * 4;
			temp[height - 1 - h][w].r = image_data[current_pixel + 0];
			temp[height - 1 - h][w].g = image_data[current_pixel + 1];
			temp[height - 1 - h][w].b = image_data[current_pixel + 2];
			temp[height - 1 - h][w].a = image_data[current_pixel + 3];
		}
	}
	std::swap(*this, temp);
}

//NB_TEXTURE_CATALOG
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

int NB::NB_Texture_Catalog::check_out(GLuint texture_id)
{
	m_texture_id_catalog.extract(texture_id);
	return m_texture_id_catalog.count(texture_id);
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


//NB_TEXTURE
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
		int color_channels;//TODO use color_channels

		stbi_set_flip_vertically_on_load(1);
		std::unique_ptr<GLubyte, decltype(stbi_image_free)*> image_data(reinterpret_cast<GLubyte*>(stbi_load(file_name.c_str(), &m_width, &m_height, &color_channels, 4)), stbi_image_free);

		if (image_data.get() == nullptr)
		{
			NB::error_log("NB::NB_Texture::NB_Texture", "Texture loading fail: " + file_name);
		}
		else
		{
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.get());
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
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


NB::NB_Texture::NB_Texture(const NB_Pixel_Map& pixel_map, NB_Texture_Type type)
	:
	m_type(type),
	m_path("none")
{
	NB::event_log("NB_Texture", "create rgba image");
	update(pixel_map, true);
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
	m_path     (rhs.m_path),
	m_width    (rhs.m_width),
	m_height   (rhs.m_height)
{
	NB_Texture_Catalog::catalog().check_in(rhs.m_id);
}

void NB::swap(NB_Texture& lhs, NB_Texture& rhs)
{
	using std::swap;
	swap(lhs.m_id    , rhs.m_id);
	swap(lhs.m_type  , rhs.m_type);
	swap(lhs.m_path  , rhs.m_path);
	swap(lhs.m_width , rhs.m_width);
	swap(lhs.m_height, rhs.m_height);
}

NB::NB_Texture& NB::NB_Texture::operator=(const NB_Texture& right)
{
	if (this->m_path != "none")
		NB_Texture_Catalog::catalog().check_out(this->m_path, this->m_id);
	else
		NB_Texture_Catalog::catalog().check_out(this->m_id);
	NB::NB_Texture temp(right);
	NB::swap(*this, temp);
	return *this;
}


void NB::NB_Texture::update(const NB_Pixel_Map& pixel_map, bool create_new_sampler)
{
	if(!create_new_sampler)
		NB::event_log("NB_Texture", "update rgba image");
	if (create_new_sampler)
		glGenTextures(1, &m_id);

	if (pixel_map.size() == 0)
		error_log("NB::NB_Texture::update", "pixel vector is empty");

	m_height = pixel_map.width();
	m_width  = pixel_map.height();
	auto&& image_data = pixel_map.convert_to_gl_data();

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.get());
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	if (create_new_sampler)
		NB::NB_Texture_Catalog::catalog().check_in(m_id);
}

NB::NB_Pixel_Map NB::NB_Texture::get_pixel_map()
{
	std::unique_ptr<GLubyte, decltype(free)*> image_data(reinterpret_cast<GLubyte*>(malloc(m_width * m_height * 4 * sizeof(GLubyte))), free);
	glGetTextureImage(m_id, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_width * m_height * 4 * sizeof(GLubyte), image_data.get());

	NB_Pixel_Map pixel_map(0, 0); 
	pixel_map.convert_from_gl_data(image_data.get(), m_width, m_height);
	
	return pixel_map;
}

