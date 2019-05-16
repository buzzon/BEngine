#include "Window.h"
#include "Message.h"

void window::create_window(const int width,
						   const int height,
						   const char * title,
						   GLFWmonitor * monitor,
						   GLFWwindow * share) {
	window_ = glfwCreateWindow(width, height, title, monitor, share);
	if (window_ == nullptr) {
		glfwTerminate();
		CauseExeption("Failed to create GLFW window.");
	}
	else {
		glViewport(0, 0, width, height);
		glfwMakeContextCurrent(window_);

		glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // захватить курсор и скрыть указатель мыши
	}
}

void window::set_key_callback(const GLFWkeyfun key_callback) const
{
	glfwSetKeyCallback(window_, key_callback);
}

void window::set_mouse_callback(const GLFWcursorposfun mouse_callback) const
{
	glfwSetCursorPosCallback(window_, mouse_callback);
}

void window::set_cursor_pos(const GLint x_pos, const GLint y_pos) const
{
	glfwSetCursorPos(window_, x_pos, y_pos);
}

void window::swap_buffers() const
{
	glfwSwapBuffers(window_);
}

bool window::window_should_close() const
{
	return glfwWindowShouldClose(window_);
}

void window::make_context_current() const
{
	glfwMakeContextCurrent(window_);
}