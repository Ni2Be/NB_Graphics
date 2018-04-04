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

namespace NB
{
	class NB_Object;

	class NB_Shader
	{
	public:
		NB_Shader() {}

		virtual void draw() {}
		void         use();
		virtual void update(NB_Object* object) {}
		
		int program() { return m_program; }
		virtual void attach(NB_Object& object);
	protected:
		std::vector<NB_Object*> objects;

		GLuint m_program;

		explicit NB_Shader(const std::string& file_name);
		~NB_Shader();

		virtual void bind_uniforms() {}

		GLuint create_shader(const std::string& text, const GLenum sader_type);

		void build_program(const std::string& file_name);

		void error_check  (GLuint             shader, 
			               GLuint             flag, 
			               bool               isProgram,
			               const std::string& errorMessage, 
			               const std::string& file_name);

	private:
		//no copy
		NB_Shader(const NB_Shader&) {}
		NB_Shader& operator=(const NB_Shader&) {}
		//
	};
}

#endif //NB_SHADER_H_INCLUDED