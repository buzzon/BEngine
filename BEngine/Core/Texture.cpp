#include "Texture.h"

GLuint Texture::LoadTexture(const char* path, GLenum target, int force_channels, GLenum format)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(target, texture);

	SetTextureParam(target, GL_REPEAT);
	SetTextureFilter(target, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, force_channels);
	glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(target);
	SOIL_free_image_data(image);
	glBindTexture(target, 0);

	return texture;
}

void Texture::SetTextureParam(GLenum target, GLint param)
{
	glTexParameteri(target, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, param);
}

void Texture::SetTextureFilter(GLenum target, GLint param)
{
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, param);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, param);
}
