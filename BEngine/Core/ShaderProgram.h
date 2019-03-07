#pragma once
#include <GL/glew.h>;
#include "Shader.h"

class ShaderProgram
{
public:
	void AddShader(GLenum shaderType, const char * path);
	void CreateProgram();
	GLint program;
private:
	Shader shader;
	GLint success;
	GLchar infoLog[infoLogSize];
};