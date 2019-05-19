#include "ShaderProgram.h"
#include "Tools.h"
#include "Message.h"
#include <glm/gtc/type_ptr.inl>

void shader_program::add_shader(const GLenum shader_type, const char * path)
{
	const auto shader = load_shader(shader_type, path);
	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success_);
	if (!success_) {
		glGetProgramInfoLog(program, log_size, nullptr, info_log_);
		error_message("SHADER_PROGRAM::COMPILATION_FAILED\n" + std::string(info_log_) );
	}

	glDeleteShader(shader);
}

void shader_program::create_program()
{
	program = glCreateProgram();
}

void shader_program::use() const
{
	glUseProgram(this->program);
}

void shader_program::set_vec3(const GLchar * name, const float x, const float y, const float z) const
{
	const auto data = glGetUniformLocation(this->program, name);
	glUniform3f(data, x, y, z);
}

void shader_program::set_vec3(const GLchar * name, const glm::vec3& vec) const
{
	glUniform3f(glGetUniformLocation(this->program, name), vec.x, vec.y, vec.z);
}

void shader_program::set_float(const GLchar * name, const float value) const
{
	glUniform1f(glGetUniformLocation(this->program, name), value);
}

void shader_program::set_int(const char* name, const int value) const
{
	glUniform1i(glGetUniformLocation(this->program, name), value);
}

void shader_program::set_mat4(const GLchar* name, const glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, GL_FALSE, glm::value_ptr(mat4));
}

GLint shader_program::load_shader(const GLenum shader_type, const char * path)
{
	auto shader_source = tools::read_file(path);

	const GLint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success_);
	if (!success_) {
		glGetShaderInfoLog(shader, log_size, nullptr, info_log_);
		error_message(std::to_string(shader_type) + "_SHADER::COMPILATION_FAILED\n" + std::string(info_log_));
	}

	return shader;
}
