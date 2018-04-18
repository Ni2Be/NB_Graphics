//TESTED

#include "NB_Standard_Shader.h"
#include "NB_Utility.h"

//DEBUG
#include <iostream>

//GLM
#include <glm/gtc/type_ptr.hpp>


void NB::NB_Standard_Shader::bind_uniforms()
{
	//TODO light
	uni_point_light_count = glGetUniformLocation(m_program, "point_light_count");
	for (int i = 0; i < C_MAX_POINT_LIGHT_COUNT; i++)
	{
		std::string num = std::to_string(i);

		uni_attenuation_const.push_back     (glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_const").c_str()));
		uni_attenuation_lin.push_back       (glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_lin").c_str()));
		uni_attenuation_quad.push_back      (glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_quad").c_str()));
		uni_light_pos.push_back             (glGetUniformLocation(m_program, ("point_lights[" + num + "].position").c_str()));
		uni_light_color.push_back           (glGetUniformLocation(m_program, ("point_lights[" + num + "].color").c_str()));
		uni_light_strength.push_back        (glGetUniformLocation(m_program, ("point_lights[" + num + "].strength").c_str()));
		uni_light_ambient_strength.push_back(glGetUniformLocation(m_program, ("point_lights[" + num + "].ambient_strength").c_str()));
	}
	uni_dir_light_direction           = glGetUniformLocation(m_program, "dir_light.direction");
	uni_dir_light_color               = glGetUniformLocation(m_program, "dir_light.color");
	uni_dir_light_strength            = glGetUniformLocation(m_program, "dir_light.strength");

	//Material
	uni_material_shininess = glGetUniformLocation(m_program, "material.shininess");
	uni_material_ambient   = glGetUniformLocation(m_program, "material.ambient");
	uni_material_diffuse   = glGetUniformLocation(m_program, "material.diffuse");
	uni_material_specular  = glGetUniformLocation(m_program, "material.specular");
	//textures
	//TODO set location dynamically
	NB_Shader::use();
	texture_unit_diffuse_map = 0;
	glUniform1i(glGetUniformLocation(NB_Shader::m_program, "diffuse_map"), texture_unit_diffuse_map);
	
	texture_unit_specular_map = 1;
	glUniform1i(glGetUniformLocation(NB_Shader::m_program, "specular_map"), texture_unit_specular_map);

	texture_unit_normal_map = 2;
	glUniform1i(glGetUniformLocation(NB_Shader::m_program, "normal_map"), texture_unit_normal_map);
	
	texture_unit_height_map = 3;
	glUniform1i(glGetUniformLocation(NB_Shader::m_program, "height_map"), texture_unit_height_map);
	
	uni_has_diffuse_map	 = glGetUniformLocation(NB_Shader::m_program, "has_diffuse_map");
	uni_has_specular_map = glGetUniformLocation(NB_Shader::m_program, "has_specular_map");
	uni_has_normal_map	 = glGetUniformLocation(NB_Shader::m_program, "has_normal_map");
	uni_has_height_map   = glGetUniformLocation(NB_Shader::m_program, "has_height_map");

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
	//Material
	glUniform1f(uni_material_shininess, material.shininess());
	glUniform3f(uni_material_ambient  , material.ambient().r , material.ambient().g , material.ambient().b);
	glUniform3f(uni_material_diffuse  , material.diffuse().r , material.diffuse().g , material.diffuse().b);
	glUniform3f(uni_material_specular , material.specular().r, material.specular().g, material.specular().b);

	//TODO check performace
	if (material.has_diffuse_map())
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit_diffuse_map);
		glBindTexture(GL_TEXTURE_2D, material.diffuse_map().id());
		glUniform1i(uni_has_diffuse_map, GL_TRUE);
	}
	else
		glUniform1i(uni_has_diffuse_map, GL_FALSE);
	if (material.has_specular_map())
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit_specular_map);
		glBindTexture(GL_TEXTURE_2D, material.specular_map().id());
		glUniform1i(uni_has_specular_map, GL_TRUE);
	}
	else
		glUniform1i(uni_has_specular_map, GL_FALSE);
	if (material.has_normal_map())
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit_normal_map);
		glBindTexture(GL_TEXTURE_2D, material.normal_map().id());
		glUniform1i(uni_has_normal_map, GL_TRUE);
	}
	else
		glUniform1i(uni_has_normal_map, GL_FALSE);
	if (material.has_height_map())
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit_height_map);
		glBindTexture(GL_TEXTURE_2D, material.height_map().id());
		glUniform1i(uni_has_height_map, GL_TRUE);
	}
	else
		glUniform1i(uni_has_height_map, GL_FALSE);
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

void NB::NB_Standard_Shader::update_light(NB::NB_Directional_Light& dir_light)
{
	glUniform3fv(uni_dir_light_direction       , 1, glm::value_ptr(dir_light.direction()));
	glUniform3fv(uni_dir_light_color           , 1, glm::value_ptr(dir_light.color()));
	glUniform1f (uni_dir_light_strength        , dir_light.strength());
	glUniform1f (uni_dir_light_ambient_strength, dir_light.ambient_strength());
}

void NB::NB_Standard_Shader::update_light(std::vector<NB::NB_Point_Light>& point_lights)
{
	//Light
	for(int i = 0; i < point_lights.size(); i++)
	{
		glUniform1f(uni_attenuation_const[i]     , point_lights[i].attenuation_const());
		glUniform1f(uni_attenuation_lin[i]       , point_lights[i].attenuation_lin());
		glUniform1f(uni_attenuation_quad[i]      , point_lights[i].attenuation_quad());
		glUniform1f(uni_light_ambient_strength[i], point_lights[i].ambient_strength());

		glUniform3f(uni_light_pos[i]             , point_lights[i].position().x, point_lights[i].position().y, point_lights[i].position().z);
		glUniform3f(uni_light_color[i]           , point_lights[i].color().r, point_lights[i].color().g, point_lights[i].color().b);
		glUniform1f(uni_light_strength[i]        , point_lights[i].strength());
	}

	glUniform1i(uni_point_light_count, point_lights.size());
}
