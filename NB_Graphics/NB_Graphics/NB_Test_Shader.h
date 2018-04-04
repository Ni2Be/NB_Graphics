/*
NB_Test_Shader:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_TEST_SHADER_H_INCLUDED
#define NB_TEST_SHADER_H_INCLUDED

//STL
#include <vector>

//
#include "NB_Shader.h"
#include "NB_Transformer.h"
#include "NB_Camera.h"
#include "NB_Light.h"
#include "NB_Object.h"

namespace NB
{
	class NB_Object;

	namespace Test
	{

		class Test_Shader_Texture : public NB::NB_Shader
		{
		public:
			Test_Shader_Texture(int light_count)
				:
				NB::NB_Shader             (),
				shader_location           ("../../res/shader/test_shader_texture"),
				light_count               (light_count),
				uni_attenuation_const     (light_count),
				uni_attenuation_lin       (light_count),
				uni_attenuation_quad      (light_count),
				uni_light_strength        (light_count),
				uni_light_pos             (light_count),
				uni_light_color           (light_count),
				uni_light_ambient_strength(light_count)
			{
				change_light_count(light_count);
				bind_uniforms();
			}

			void attach(NB_Camera&              camera);
			void attach(NB_Directional_Light&   dir_light);
			void attach(NB_Light&               light);
			void attach(std::vector<NB_Light>&  lights);

			void draw();

			void update(NB_Object* object);

			void update(
				NB_Camera&              cam,
				NB_Object&              object,
				NB_Directional_Light&   ambient,
				std::vector<NB_Light*>& lights);
		protected:
			NB_Directional_Light*       m_dir_light;
			std::vector<NB_Light*>      m_lights;
			NB_Camera*                  m_camera;

			std::string shader_location;

			void bind_uniforms();
			GLint uni_projection;
			GLint uni_view;
			GLint uni_transform;

			GLint uni_camera_pos;

			GLint uni_material_ambient;
			GLint uni_material_diffuse;
			GLint uni_material_specular;
			GLint uni_material_shininess;

			//should be called before gameloop
			//recompiles shader program
			void change_light_count(int new_count);

			int light_count;

			std::vector<GLint> uni_attenuation_const;
			std::vector<GLint> uni_attenuation_lin;
			std::vector<GLint> uni_attenuation_quad;
			std::vector<GLint> uni_light_strength;
			std::vector<GLint> uni_light_pos;
			std::vector<GLint> uni_light_color;
			std::vector<GLint> uni_light_ambient_strength;

			GLint uni_dir_light_direction;
			GLint uni_dir_light_color;
			GLint uni_dir_light_strength;

			GLint uni_material_texture;
			GLint uni_material_specular_map;
		};

	}
}
#endif
