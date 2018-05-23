#include "NB_Texture.h"
#include "NB_Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb-master/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb-master/stb_image_write.h>

#include <iostream>
#include <algorithm>


//TODO use smartpointer
//TODO should store image and provide a way to manipulate it

//NB_PIXEL
NB::NB_Pixel::NB_Pixel(const glm::vec4& vec, bool multiply_255)
{
	if (multiply_255)
	{
		r = vec.r * 255;
		g = vec.g * 255;
		b = vec.b * 255;
		a = vec.a * 255;
	}
}

NB::NB_Pixel::NB_Pixel(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	:
	r(r), g(g), b(b), a(a)
{}

std::ostream& NB::operator<<(std::ostream& stream, const NB_Pixel& pixel)
{
	return stream
		<< "(" << (int)pixel.r 
		<< ", " << (int)pixel.g
		<< ", " << (int)pixel.b
		<< ")";
}


//NB_PIXEL_MAP
NB::NB_Pixel_Map::NB_Pixel_Map(const std::string file_path)
{
	NB::event_log("NB::NB_Pixel_Map::NB_Pixel_Map(const std::string file_path)", "loading: " + file_path);
	int color_channels;
	stbi_set_flip_vertically_on_load(1);
	std::unique_ptr<GLubyte, decltype(stbi_image_free)*> 
		image_data(reinterpret_cast<GLubyte*>(stbi_load(file_path.c_str(), &m_width, &m_height, &color_channels, 4)), stbi_image_free);

	if (image_data.get() == nullptr)
	{
		NB::error_log("NB::NB_Pixel_Map::NB_Pixel_Map", "Texture loading fail: " + file_path);
	}

	this->convert_from_bit_data(image_data.get(), m_width, m_height);
}


NB::NB_Pixel_Map::NB_Pixel_Map(const std::initializer_list<std::initializer_list<NB::NB_Pixel>>& il)
	:
	m_height(il.size()),
	m_width(il.begin()->size())
{
	m_pixel.reserve(il.size() * il.begin()->size());

	for (auto it = std::rbegin(il); it != std::rend(il); it++)
		for (auto& pixel : *it)
		{
			m_pixel.push_back(pixel);
			if (it->size() != m_width)
				NB::error_log("NB::NB_Pixel_Map::NB_Pixel_Map(const std::initializer_list<std::vector<NB::NB_Pixel>>& il)", "initializer_list width varies");
		}
}

void NB::NB_Pixel_Map::save_file(const std::string file_path)
{
	NB::event_log("NB::NB_Pixel_Map::save_to_file(const std::string file_path)", "saving to: " + file_path + ".bmp");
	stbi_flip_vertically_on_write(1);
	stbi_write_bmp((file_path + ".bmp").c_str(), this->width(), this->height(), STBI_rgb_alpha, &(m_pixel.begin()->r));
}

void NB::NB_Pixel_Map::convert_from_bit_data(GLubyte* image_data, int width, int height)
{
	this->m_height = height;
	this->m_width  = width;
	m_pixel.reserve(width * height);
	for (int i = 0; i < width * height * 4; i += 4)
	{
		m_pixel.push_back(
			NB_Pixel(
				image_data[i],
				image_data[i + 1],
				image_data[i + 2],
				image_data[i + 3]
				)
		);
	}
}

//NB_TEXTURE_CATALOG
bool NB::NB_Texture_Catalog::check(std::string path)
{
	return !m_texture_catalog.count(path);
}

void NB::NB_Texture_Catalog::check_in(std::string path, GLuint texture_id)
{
	m_texture_catalog[path] = texture_id;
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
		NB::event_log("NB::NB_Texture::NB_Texture(const std::string& file_name, NB_Texture_Type type)", "loading: " + file_name);

		NB_Pixel_Map pixel_map(file_name);
		create_new_sampler(pixel_map);

		//registrate new texture path
		NB_Texture_Catalog::catalog().check_in(file_name, this->m_id);
	}
	//texture is loaded
	else
	{
		NB::event_log("NB::NB_Texture::NB_Texture(const std::string& file_name, NB_Texture_Type type)", "from texture catalog: " + file_name);
		this->m_id = NB_Texture_Catalog::catalog().get_id(file_name);
		NB_Texture_Catalog::catalog().check_in(this->m_id);
	}
}


NB::NB_Texture::NB_Texture(const NB_Pixel_Map& pixel_map, NB_Texture_Type type)
	:
	m_type(type),
	m_path("none")
{
	NB::event_log("NB::NB_Texture::NB_Texture(const NB_Pixel_Map& pixel_map, NB_Texture_Type type)", "create rgba image");
	create_new_sampler(pixel_map);
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


void NB::NB_Texture::update(const NB_Pixel_Map& pixel_map)
{
	NB::event_log("NB::NB_Texture::update(const NB_Pixel_Map& pixel_map)", "update rgba image");

	if (pixel_map.is_empty())
		error_log("NB::NB_Texture::update(const NB_Pixel_Map& pixel_map)", "pixel vector is empty");

	m_height = pixel_map.width();
	m_width  = pixel_map.height();

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_map.get_data_pointer());
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);

}

void NB::NB_Texture::create_new_sampler(const NB_Pixel_Map& pixel_map)
{
	NB::event_log("NB::NB_Texture::create_new_sampler(const NB_Pixel_Map& pixel_map)", "prepare rgba image");
	glGenTextures(1, &m_id);
	update(pixel_map);
	NB::NB_Texture_Catalog::catalog().check_in(m_id);
}

NB::NB_Pixel_Map NB::NB_Texture::get_pixel_map()
{
	//std::vector<GLubyte> image_data(m_width * m_height * 4);

	NB_Pixel_Map pixel_map(m_width, m_height);

	glGetTextureImage(m_id, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_map.height() * pixel_map.width() * 4 * sizeof(GLubyte), pixel_map.get_data_pointer());
	//
	//NB_Pixel_Map pixel_map(0, 0); 
	//pixel_map.convert_from_bit_data(image_data.data(), m_width, m_height);
	
	return pixel_map;
}

