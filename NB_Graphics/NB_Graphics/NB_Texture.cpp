#include "NB_Texture.h"
#include "NB_Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>


NB::NB_Texture::NB_Texture(const std::string& file_name, NB_Texture_Type type)
	:
	m_type(type),
	m_file_path(file_name)
{	//load picture
	int width, height, color_channels;

	stbi_set_flip_vertically_on_load(0);
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

		stbi_image_free(image_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
