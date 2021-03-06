//TESTED

/*
NB_Base_Shader:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_STANDARD_SHADER_H_INCLUDED
#define NB_STANDARD_SHADER_H_INCLUDED

//GLEW
#include <GL/glew.h>

//STL
#include <string>
#include <vector>
#include <memory>

//NB
#include "NB_Shader.h"
#include "NB_Transform.h"
#include "NB_Illumination.h"
#include "NB_Camera.h"
#include "NB_Material.h"


namespace NB
{
	class NB_Object;

	class NB_Standard_Shader : public NB_Shader
	{
	public:
		static NB_Standard_Shader& shader()
		{
			static NB_Standard_Shader static_shader;
			return static_shader;
		}
		void bind_uniforms();

		void update_material(NB::NB_Material& material);
		void update_transform(NB::NB_Transform& transform);
		void update_light(NB::NB_Directional_Light& dir_light);
		void update_light(std::vector<NB::NB_Point_Light>& point_light);
		void update_camera(NB::NB_Camera& camera);


		//material
		GLint uni_material_ambient;
		GLint uni_material_diffuse;
		GLint uni_material_specular;
		GLint uni_material_shininess;

		//textures (not really used as uniforms, just to mention they exist in shader)
		GLint texture_unit_diffuse_map;
		GLint texture_unit_specular_map;
		GLint texture_unit_normal_map;
		GLint texture_unit_height_map;

		GLint uni_has_diffuse_map;
		GLint uni_has_specular_map;
		GLint uni_has_normal_map;
		GLint uni_has_height_map;

		//oject
		GLint uni_transform;

		//camera
		GLint uni_camera_pos;
		GLint uni_projection;
		GLint uni_view;

		//point light
		const int C_MAX_POINT_LIGHT_COUNT = 32;
		GLint uni_point_light_count;
		std::vector<GLint> uni_light_attenuation_const;
		std::vector<GLint> uni_light_attenuation_lin;
		std::vector<GLint> uni_light_attenuation_quad;
		std::vector<GLint> uni_light_strength;
		std::vector<GLint> uni_light_pos;
		std::vector<GLint> uni_light_color;
		std::vector<GLint> uni_light_ambient_strength;

		//dir light
		GLint uni_dir_light_direction;
		GLint uni_dir_light_color;
		GLint uni_dir_light_ambient_strength;
		GLint uni_dir_light_strength;
	private:
		//use NB_Standard_Shader::shader() to use the static shader object
		NB_Standard_Shader()
			:
			NB::NB_Shader("../res/standard shader/standard_texture_shader")
		{
			bind_uniforms();
		}
		NB_Standard_Shader(const NB_Standard_Shader&);
		NB_Standard_Shader& operator=(const NB_Standard_Shader&);
	};
}

#endif
