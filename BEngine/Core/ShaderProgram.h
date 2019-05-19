#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>

constexpr int log_size = 1024;

class shader_program
{
public:
	void add_shader(GLenum shader_type, const char * path);
	void create_program();
	void use() const;
	void set_vec3(const GLchar *name, float x, float y, float z) const;
	void set_vec3(const GLchar * name, const glm::vec3& vec) const;
	void set_float(const GLchar* name, float value) const;
	void set_int(const char* name, int value) const;
	void set_mat4(const GLchar * name, const glm::mat4& mat4) const;
	GLint program{};
private:
	GLint success_ = 0;
	GLchar info_log_[log_size] = {};
	GLint load_shader(GLenum shader_type, const char * path);
};