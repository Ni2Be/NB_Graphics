#pragma once
#include <NB_Graphics/NB_Shader.h>
#include <NB_Graphics/NB_Transform.h>

#include <string>

#include <glm/gtc/type_ptr.hpp>

#include <NB_Graphics/NB_Directional_Light.h>

namespace NB_Test
{
	class NB_Simple_Test_Shader : public NB::NB_Shader
	{
	public:
		NB_Simple_Test_Shader(const std::string path)
			:
			NB::NB_Shader(path)
		{
			bind_uniforms();
		}


		int	uni_material_texture;

		void bind_uniforms();

		void update_transform(NB::NB_Transform& transform);
		void update_dir_light(NB::NB_Directional_Light& dir_light);
		void update_camera(NB::NB_Camera& camera);

		//oject
		GLint uni_transform;

		//camera
		GLint uni_camera_pos;
		GLint uni_projection;
		GLint uni_view;

		//dir light
		GLint uni_dir_light_direction;
		GLint uni_dir_light_color;
		GLint uni_dir_light_ambient_strength;
		GLint uni_dir_light_strength;
	};

	void NB_Simple_Test_Shader::bind_uniforms()
	{
		//material
		glGetUniformLocation(NB_Shader::m_program, "texture");

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

	void NB_Simple_Test_Shader::update_transform(NB::NB_Transform& transform)
	{
		//Transform
		glUniformMatrix4fv(uni_transform, 1, GL_FALSE, glm::value_ptr(transform.get_model()));
	}

	void NB_Simple_Test_Shader::update_camera(NB::NB_Camera& camera)
	{
		//Camera
		glUniformMatrix4fv(uni_view      , 1, GL_FALSE, glm::value_ptr(camera.view()));
		glUniformMatrix4fv(uni_projection, 1, GL_FALSE, glm::value_ptr(camera.projection()));
		glUniform3fv      (uni_camera_pos, 1, glm::value_ptr(camera.pos()));
	}

	void NB_Simple_Test_Shader::update_dir_light(NB::NB_Directional_Light& dir_light)
	{
		glUniform3fv(uni_dir_light_direction, 1, glm::value_ptr(dir_light.direction()));
		glUniform3fv(uni_dir_light_color, 1, glm::value_ptr(dir_light.color()));
		glUniform1f (uni_dir_light_strength, dir_light.strength());
		glUniform1f (uni_dir_light_ambient_strength, dir_light.ambient_strength());
	}
}
