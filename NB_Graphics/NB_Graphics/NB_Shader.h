//TESTED

/*
NB_Shader:
Attention:
Purpose:
Base shader class should be inherited and expanded with
the needed attach and bind_uniforms functions
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_SHADER_H_INCLUDED
#define NB_SHADER_H_INCLUDED

//GLEW
#include <GL/glew.h>

//STL
#include <string>
#include <vector>
#include <memory>

//NB
#include "NB_Camera.h"

namespace NB
{
	class NB_Object;
	class NB_Material;
	class NB_Transform;
	class NB_Light;

	class NB_Shader
	{
	public:
		//functions
		void use();
		void attach(NB_Camera& camera);

		//get/set
		NB_Camera& camera()  { return *m_camera; }

		const int        program() const { return m_program; }
		const NB_Camera& camera()  const { return *m_camera; }
		
		//virtual
		//virtual void draw() {}
		virtual void update_transform(NB::NB_Transform& transform) {}
		virtual void update_light    (NB::NB_Light& dir_light) {}
		virtual void update_camera   (NB::NB_Camera& camera) {}
		virtual void update_material (NB::NB_Material& material) {}
		virtual void bind_uniforms   () {}

	protected:
		//constructor
		NB_Shader() {}
		explicit NB_Shader(const std::string file_name);
		//destructor
		~NB_Shader();

		//member
		GLuint                  m_program;
		NB_Camera*              m_camera;

		//functions
		GLuint create_shader(const std::string& text, const GLenum shader_type);
		void build_program(const std::string& file_name);
		enum NB_Check_Type {NB_PROGRAM, NB_SHADER};
		void error_check  (GLuint             check_object_id,
			               GLuint             flag, 
			               NB_Check_Type      check_type,
			               const std::string& error_message, 
			               const std::string& file_name);
	private:
		//TODO implement copy
		NB_Shader(const NB_Shader&) {}
		NB_Shader& operator=(const NB_Shader&) {}
		//

	};
}

#endif //NB_SHADER_H_INCLUDED