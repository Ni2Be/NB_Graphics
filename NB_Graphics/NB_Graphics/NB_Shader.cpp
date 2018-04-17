//TESTED

#include "NB_Shader.h"
#include "NB_Utility.h"

//DEBUG
#include <iostream>

NB::NB_Shader::NB_Shader(const std::string file_name)
	:
	m_program(-1)
{
	build_program(file_name);
}

NB::NB_Shader::~NB_Shader()
{
	glDeleteProgram(m_program);
}

void NB::NB_Shader::attach(NB_Camera& camera)
{
	this->m_camera = &camera;
}

void NB::NB_Shader::build_program(const std::string& file_name)
{
	if (m_program != -1)
	{
		glDeleteProgram(m_program);
	}
	m_program = glCreateProgram();

	NB::event_log("NB::NB_Shader::build_program", "loading shader: " + file_name);

	//compile shaders
	GLuint vetex_shader    = create_shader(file_name + ".vert", GL_VERTEX_SHADER);
	GLuint fragment_shader = create_shader(file_name + ".frag", GL_FRAGMENT_SHADER);

	//link to program
	glAttachShader(m_program, vetex_shader);
	glAttachShader(m_program, fragment_shader);

	glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);
	error_check(m_program, GL_LINK_STATUS, NB_PROGRAM, "Shader linking fail: ", file_name);

	glValidateProgram(m_program);
	error_check(m_program, GL_VALIDATE_STATUS, NB_PROGRAM, "Program is invalid: ", file_name);

	glDeleteShader(vetex_shader);
	glDeleteShader(fragment_shader);
}

void NB::NB_Shader::use()
{
	glUseProgram(m_program);
}

GLuint NB::NB_Shader::create_shader(const std::string& file_name, const GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);
	if (shader == 0)
		error_log("NB::NB_Shader::create_shader", "Shader creation failed");

	std::string   file_content = load_file_to_string(file_name).c_str();
	const GLchar* shader_code  = static_cast<const GLchar*>(file_content.c_str());

	glShaderSource (shader, 1, &shader_code, NULL);
	glCompileShader(shader);

	error_check(shader, GL_COMPILE_STATUS, NB_SHADER, "Shader compilation fail: ", file_name);

	return shader;
}

void NB::NB_Shader::error_check(GLuint check_object_id, GLuint flag, NB_Check_Type check_type, const std::string& error_message, const std::string& file_name)
{
	GLint success = 0;
	switch (check_type)
	{
	case NB_PROGRAM:
		glGetProgramiv(check_object_id, flag, &success); break;
	case NB_SHADER:
		glGetShaderiv(check_object_id, flag, &success); break;
	}
	if (success == GL_FALSE)
	{
		GLchar error[1024] = { 0 };
		switch (check_type)
		{
		case NB_PROGRAM:
			glGetProgramInfoLog(check_object_id, sizeof(error), NULL, error); break;
		case NB_SHADER:
			glGetShaderInfoLog(check_object_id, sizeof(error), NULL, error); break;
		}
		error_log("NB::NB_Shader::error_check\n", "Error in " + file_name + "\n" + error_message + error);
	}
}
