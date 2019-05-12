#include "ShaderProgram.h"

void ShaderProgram::AddShader(GLenum shaderType, const char * path)
{
	GLint shader = LoadShader(shaderType, path);
	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
		ErrorMessage("SHADER_PROGRAMM::COMPILATION_FAILED\n" + std::string(infoLog) );
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

void ShaderProgram::setVec3(const GLchar * name, float x, float y, float z)
{
	GLint lightColorLoc = glGetUniformLocation(this->program, name);
	glUniform3f(lightColorLoc, x, y, z);
}

void ShaderProgram::setVec3(const GLchar * name, glm::vec3 vec)
{
	GLint lightColorLoc = glGetUniformLocation(this->program, name);
	glUniform3f(lightColorLoc, vec.x, vec.y, vec.z);
}

void ShaderProgram::setFloat(const GLchar * name, float value)
{
	GLint lightColorLoc = glGetUniformLocation(this->program, name);
	glUniform1f(lightColorLoc, value);
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
		ErrorMessage(std::to_string(shaderType) + "_SHADER::COMPILATION_FAILED\n" + std::string(infoLog));
	}

	return shader;
}
