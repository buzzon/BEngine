#include "BEngine.h"
#include "Message.h"

void b_engine::write_specifications() const
{
	message("Maximum nr of vertex attributes supported: " + std::to_string(get_max_nr()));
}

void b_engine::calculate_delta_time() {
	const GLfloat current_frame = glfwGetTime();
	delta_time_ = current_frame - last_frame_;
	last_frame_ = current_frame;
}

void b_engine::set_enables(GLenum cap, ...)
{
	auto p = &cap;
	while (*p) {
		glEnable(cap);
		p++;
	}
}

GLfloat b_engine::get_delta_time() const
{
	return delta_time_;
}

int b_engine::get_max_nr() {
	GLint nr_attributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr_attributes);
	return nr_attributes;
}

b_engine::b_engine() {
	message("Initializing GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_ver_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_ver_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	message("Starting engine");
}

b_engine::~b_engine() {
	message("Successfully disabled!");
}

void b_engine::using_glew() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cause_exeption("Failed to initialize GLEW.");
}
