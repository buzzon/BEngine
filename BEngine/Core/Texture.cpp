#include "Texture.h"

GLuint texture::load_texture(const char* path, const GLenum target, const int force_channels, const GLenum format)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(target, texture);

	set_texture_param(target, GL_REPEAT);
	set_texture_filter(target, GL_LINEAR);

	int width, height;
	const auto image = SOIL_load_image(path, &width, &height, 0, force_channels);
	glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(target);
	SOIL_free_image_data(image);
	glBindTexture(target, 0);

	return texture;
}

void texture::set_texture_param(const GLenum target, const GLint param)
{
	glTexParameteri(target, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, param);
}

void texture::set_texture_filter(const GLenum target, const GLint param)
{
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, param);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, param);
}
