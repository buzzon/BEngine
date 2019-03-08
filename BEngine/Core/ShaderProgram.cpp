#include "ShaderProgram.h"

void ShaderProgram::AddShader(GLenum shaderType, const char * path)
{
	GLint shader = LoadShader(shaderType, path);
	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAMM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(shader);
}

void ShaderProgram::CreateProgram()
{
	program = glCreateProgram();
}

void ShaderProgram::Use()
{
	glUseProgram(this->program);
}

GLint ShaderProgram::LoadShader(GLenum shaderType, const char * path)
{
	const GLchar* ShaderSource = Tools::ReadFile(path);

	GLint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &ShaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}
