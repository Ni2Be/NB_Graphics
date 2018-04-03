#include "NB_Test_Shader.h"

#include "NB_Utility.h"

//STL
#include <string>

//GLM
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


#include <iostream>

void NB::Test::Test_Shader_Texture::bind_uniforms()
{
	uni_transform  = glGetUniformLocation(m_program, "transform");
	uni_view       = glGetUniformLocation(m_program, "view");
	uni_projection = glGetUniformLocation(m_program, "projection");

	for (int i = 0; i < light_count; i++)
	{
		std::string num               = std::to_string(i);
		uni_attenuation_const[i]      = glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_const").c_str());
		uni_attenuation_lin[i]        = glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_lin").c_str());
		uni_attenuation_quad[i]       = glGetUniformLocation(m_program, ("point_lights[" + num + "].attenuation_quad").c_str());
		uni_light_pos[i]              = glGetUniformLocation(m_program, ("point_lights[" + num + "].position").c_str());
		uni_light_color[i]            = glGetUniformLocation(m_program, ("point_lights[" + num + "].color").c_str());
		uni_light_strength[i]         = glGetUniformLocation(m_program, ("point_lights[" + num + "].strength").c_str());
		uni_light_ambient_strength[i] = glGetUniformLocation(m_program, ("point_lights[" + num + "].ambient_strength").c_str());
	}

	uni_dir_light_direction   = glGetUniformLocation(m_program, "dir_light.direction");
	uni_dir_light_color       = glGetUniformLocation(m_program, "dir_light.color");
	uni_dir_light_strength    = glGetUniformLocation(m_program, "dir_light.strength");

	uni_camera_pos            = glGetUniformLocation(m_program, "camera_pos");

	uni_material_shininess    = glGetUniformLocation(m_program, "material.shininess");
	uni_material_ambient      = glGetUniformLocation(m_program, "material.ambient");
	uni_material_diffuse      = glGetUniformLocation(m_program, "material.diffuse");
	uni_material_specular     = glGetUniformLocation(m_program, "material.specular");

	uni_material_texture      = glGetUniformLocation(m_program, "material.texture");
	uni_material_specular_map = glGetUniformLocation(m_program, "material.specular_map");
}

void NB::Test::Test_Shader_Texture::update(NB::NB_Object* object)
{
	update(*m_camera, *object, *m_dir_light, m_lights);
}

void NB::Test::Test_Shader_Texture::update(
	NB::NB_Camera&              cam,
	NB::NB_Object&              object,
	NB::NB_Directional_Light&   dir_light,
	std::vector<NB::NB_Light*>& lights)
{
	//Transformer
	glUniformMatrix4fv(uni_transform , 1, GL_FALSE, glm::value_ptr(object.position().get_model()));

	//Camera
	glUniformMatrix4fv(uni_view      , 1, GL_FALSE, glm::value_ptr(cam.view()));
	glUniformMatrix4fv(uni_projection, 1, GL_FALSE, glm::value_ptr(cam.projection()));
	glUniform3fv      (uni_camera_pos, 1, glm::value_ptr(cam.camera_pos()));

	//Light
	for (int i = 0; i < lights.size(); i++)
	{
		glUniform1f(uni_attenuation_const[i]     , lights[i]->properties().attenuation_const);
		glUniform1f(uni_attenuation_lin[i]       , lights[i]->properties().attenuation_lin);
		glUniform1f(uni_attenuation_quad[i]      , lights[i]->properties().attenuation_quad);
		glUniform1f(uni_light_ambient_strength[i], lights[i]->properties().ambient_strength);

		glUniform3f(uni_light_pos[i]             , lights[i]->position().x  , lights[i]->position().y  , lights[i]->position().z);
		glUniform3f(uni_light_color[i]           , lights[i]->properties().color.r, lights[i]->properties().color.g, lights[i]->properties().color.b);
		glUniform1f(uni_light_strength[i]        , lights[i]->properties().strength);
	}
	//Directional Light
	glUniform3fv(uni_dir_light_direction, 1, glm::value_ptr(dir_light.direction()));
	glUniform3fv(uni_dir_light_color    , 1, glm::value_ptr(dir_light.color()));
	glUniform1f(uni_dir_light_strength  , dir_light.strength());


	//Material
	glUniform1f(uni_material_shininess, object.material().shininess * 128);
	glUniform3f(uni_material_ambient  , object.material().ambient.r , object.material().ambient.g , object.material().ambient.b);
	glUniform3f(uni_material_diffuse  , object.material().diffuse.r , object.material().diffuse.g , object.material().diffuse.b);
	glUniform3f(uni_material_specular , object.material().specular.r, object.material().specular.g, object.material().specular.b);

	//Texture
#ifdef NB_DEBUG
	if (object.material.texture == nullptr)
	{
		error_log("NB::Test::Test_Shader_Texture::update", "No texture");
		exit(EXIT_FAILURE);
	}
#endif // NB_DEBUG


	//TODO bind all textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.material().texture->id);
	glUniform1i(uni_material_texture, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, object.material().specular_map->id);
	glUniform1i(uni_material_specular_map, 1);
}

void NB::Test::Test_Shader_Texture::attach(NB::NB_Camera& camera)
{
	this->m_camera    = &camera;
}

void NB::Test::Test_Shader_Texture::attach(NB::NB_Directional_Light& dir_light)
{
	this->m_dir_light = &dir_light;
}

void NB::Test::Test_Shader_Texture::attach(NB::NB_Light& light)
{
	this->m_lights.push_back(&light);
}

void NB::Test::Test_Shader_Texture::attach(std::vector<NB::NB_Light>& lights)
{
	this->m_lights.reserve(this->m_lights.size() + lights.size());
	for (auto& l : lights)
		this->m_lights.push_back(&l);
}

void NB::Test::Test_Shader_Texture::change_light_count(int new_count)
{
	NB::search_replace(shader_location + ".frag", "const int LIGHT_COUNT = (\\d)*;", "const int LIGHT_COUNT = " + std::to_string(new_count) + ";");
	this->light_count = new_count;
	this->build_program(shader_location);
}
