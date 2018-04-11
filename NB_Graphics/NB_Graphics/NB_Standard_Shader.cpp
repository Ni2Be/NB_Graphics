//TESTED

#include "NB_Standard_Shader.h"
#include "NB_Utility.h"

//DEBUG
#include <iostream>

//GLM
#include <glm/gtc/type_ptr.hpp>

void NB::NB_Standard_Shader::bind_uniforms()
{
	//TODO material

	//textures, set locations
	NB_Shader::use();
	uni_texture_diffuse = glGetUniformLocation(NB_Shader::m_program, "diffuse_map");
	glUniform1i(uni_texture_diffuse, 0);
	uni_texture_specular_map = glGetUniformLocation(NB_Shader::m_program, "specular_map");
	glUniform1i(uni_texture_specular_map, 1);
	uni_texture_normal_map = glGetUniformLocation(NB_Shader::m_program, "normal_map");
	glUniform1i(uni_texture_normal_map, 2);
	uni_texture_height_map = glGetUniformLocation(NB_Shader::m_program, "height_map");
	glUniform1i(uni_texture_height_map, 3);

	//transform
	uni_transform  = glGetUniformLocation(NB_Shader::m_program, "transform");

	//camera
	uni_camera_pos = glGetUniformLocation(NB_Shader::m_program, "camera_pos");
	uni_view       = glGetUniformLocation(NB_Shader::m_program, "view");
	uni_projection = glGetUniformLocation(NB_Shader::m_program, "projection");

	//Directional Light
	uni_dir_light_direction        = glGetUniformLocation(NB_Shader::m_program, "dir_light.direction");
	uni_dir_light_color            = glGetUniformLocation(NB_Shader::m_program, "dir_light.color");
	uni_dir_light_ambient_strength = glGetUniformLocation(NB_Shader::m_program, "dir_light.ambient_strength");
	uni_dir_light_strength         = glGetUniformLocation(NB_Shader::m_program, "dir_light.strength");
}


void NB::NB_Standard_Shader::update_material(NB::NB_Material& material)
{
	//TODO make work
	if (material.has_diffuse_map())
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, material.diffuse_map().id());
	}
	if (material.has_specular_map())
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, material.specular_map().id());
	}
	if (material.has_normal_map())
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, material.normal_map().id());
	}
	if (material.has_height_map())
	{
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(GL_TEXTURE_2D, material.height_map().id());
	}
}

void NB::NB_Standard_Shader::update_transform(NB::NB_Transform& transform)
{
	//Transform
	glUniformMatrix4fv(uni_transform, 1, GL_FALSE, glm::value_ptr(transform.get_model()));
}

void NB::NB_Standard_Shader::update_camera(NB::NB_Camera& camera)
{
	//Camera
	glUniformMatrix4fv(uni_view      , 1, GL_FALSE, glm::value_ptr(camera.view()));
	glUniformMatrix4fv(uni_projection, 1, GL_FALSE, glm::value_ptr(camera.projection()));
	glUniform3fv      (uni_camera_pos, 1, glm::value_ptr(camera.pos()));
}

void NB::NB_Standard_Shader::update_dir_light(NB::NB_Directional_Light& dir_light)
{
	glUniform3fv(uni_dir_light_direction, 1, glm::value_ptr(dir_light.direction()));
	glUniform3fv(uni_dir_light_color, 1, glm::value_ptr(dir_light.color()));
	glUniform1f (uni_dir_light_strength, dir_light.strength());
	glUniform1f (uni_dir_light_ambient_strength, dir_light.ambient_strength());
}
