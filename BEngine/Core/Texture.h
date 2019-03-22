#include <GL/glew.h>
#include <SOIL/SOIL.h>

#pragma once
class Texture
{
public:
	static GLuint LoadTexture(const char* path, GLenum target, int force_channels, GLenum format); //GL_TEXTURE_2D SOIL_LOAD_RGB GL_RGB
private:
	static void SetTextureParam(GLenum target, GLint param);
	static void SetTextureFilter(GLenum target, GLint param);
};

