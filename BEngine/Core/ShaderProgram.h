#pragma once
#include <GL/glew.h>;
#include "Tools.h"
#include "Message.h"
#include <glm/vec3.hpp>

#define LOG_SIZE 1024

class ShaderProgram
{
public:
	void AddShader(GLenum shaderType, const char * path);
	void CreateProgram();
	void Use();
	void setVec3(const GLchar *name, float x, float y, float z);
	void setVec3(const GLchar * name, glm::vec3 vec);
	void setFloat(const GLchar *name, float value);
	GLint program;
private:
	GLint success;
	GLchar infoLog[LOG_SIZE];
	GLint LoadShader(GLenum shaderType, const char * path);
};