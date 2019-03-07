#pragma once

#include <iostream>
#include <GL/glew.h>;

const int infoLogSize = 1024;

class Shader
{
public:
	Shader();
	Shader(GLenum shaderType, const char * path);
	GLuint index;
private:
	GLint success;
	GLchar infoLog[infoLogSize];
};

