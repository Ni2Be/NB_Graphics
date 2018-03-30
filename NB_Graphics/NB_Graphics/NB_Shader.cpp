#include "NB_Shader.h"
#include "NB_Utility.h"

//GLM
#include <glm.hpp>


NB::NB_Shader::NB_Shader(const std::string& file_name)
	:
	program(-1)
{
	build_program(file_name);
}

NB::NB_Shader::~NB_Shader()
{
	glDeleteProgram(program);
}


void NB::NB_Shader::build_program(const std::string& file_name)
{
	if (program != -1)
	{
		glDeleteProgram(program);
	}
	program = glCreateProgram();

	//compile shaders
	GLuint vetex_shader    = create_shader(file_name + ".vert", GL_VERTEX_SHADER);
	GLuint fragment_shader = create_shader(file_name + ".frag", GL_FRAGMENT_SHADER);

	//link to program
	glAttachShader(program, vetex_shader);
	glAttachShader(program, fragment_shader);

	glBindAttribLocation(program, 0, "position");

	glLinkProgram(program);
	error_check(program, GL_LINK_STATUS, true, "Shader linking fail: ", file_name);

	glValidateProgram(program);
	error_check(program, GL_VALIDATE_STATUS, true, "Program is invalid: ", file_name);

	glDeleteShader(vetex_shader);
	glDeleteShader(fragment_shader);
}

void NB::NB_Shader::use()
{
	glUseProgram(program);
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

	error_check(shader, GL_COMPILE_STATUS, false, "Shader compilation fail: ", file_name);

	return shader;
}

void NB::NB_Shader::error_check(GLuint get_checked, GLuint flag, bool is_program, const std::string& error_message, const std::string& file_name)
{
	GLint success = 0;
	if (is_program)
		glGetProgramiv(get_checked, flag, &success);
	else
		glGetShaderiv (get_checked, flag, &success);

	if (success == GL_FALSE)
	{
		GLchar error[1024] = { 0 };
		if (is_program)
			glGetProgramInfoLog(get_checked, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog (get_checked, sizeof(error), NULL, error);

		error_log("NB::NB_Shader::error_check\n", "Error in " + file_name + "\n" + error_message + error);
	}
}
