#pragma once
#include <GL/glew.h>;
#include "Tools.h"

#define LOG_SIZE 1024

class ShaderProgram
{
public:
	void AddShader(GLenum shaderType, const char * path);
	void CreateProgram();
	void Use();
private:
	GLint program;
	GLint success;
	GLchar infoLog[LOG_SIZE];
	GLint LoadShader(GLenum shaderType, const char * path);
};