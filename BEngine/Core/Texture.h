#include <GL/glew.h>
#include <SOIL/SOIL.h>

#pragma once
class texture
{
public:
	static GLuint load_texture(const char* path, GLenum target, int force_channels, GLenum format); //GL_TEXTURE_2D SOIL_LOAD_RGB GL_RGB
private:
	static void set_texture_param(GLenum target, GLint param);
	static void set_texture_filter(GLenum target, GLint param);
};

