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

	class NB_Shader
	{
	public:
		//functions
		void use();
		void attach(NB_Object& object);
		void attach(NB_Camera& camera);

		//get/set
		NB_Camera& camera()  { return *m_camera; }

		const int        program() const { return m_program; }
		const NB_Camera& camera()  const { return *m_camera; }
	protected:
		//constructor
		NB_Shader() {}
		explicit NB_Shader(const std::string file_name);
		//destructor
		~NB_Shader();

		//member
		GLuint                  m_program;
		std::vector<NB_Object*> m_objects;
		NB_Camera*              m_camera;

		//functions
		GLuint create_shader(const std::string& text, const GLenum sader_type);
		void build_program(const std::string& file_name);
		void error_check  (GLuint             shader, 
			               GLuint             flag, 
			               bool               isProgram,
			               const std::string& errorMessage, 
			               const std::string& file_name);
		//virtual
		virtual void draw() {}
		virtual void update(NB_Object* object) {}
		virtual void bind_uniforms() {}
	private:
		//TODO implement copy
		NB_Shader(const NB_Shader&) {}
		NB_Shader& operator=(const NB_Shader&) {}
		//

	};
}

#endif //NB_SHADER_H_INCLUDED