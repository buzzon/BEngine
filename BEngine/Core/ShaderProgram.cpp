#include "ShaderProgram.h"

void ShaderProgram::AddShader(GLenum shaderType, const char * path)
{
	shader = Shader(shaderType, path);
	glAttachShader(program, shader.index);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, infoLogSize, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAMM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(shader.index);
}

void ShaderProgram::CreateProgram()
{
	program = glCreateProgram();
}