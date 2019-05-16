#include "Window.h"
#include "Message.h"

void Window::CreateWindow(int width,
	int height,
	const char * title,
	GLFWmonitor * monitor,
	GLFWwindow * share) {
	window = glfwCreateWindow(width, height, title, monitor, share);
	if (window == nullptr) {
		glfwTerminate();
		CauseExeption("Failed to create GLFW window.");
	}
	else {
		glViewport(0, 0, width, height);
		glfwMakeContextCurrent(window);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // захватить курсор и скрыть указатель мыши
	}
}

void Window::SetKeyCallback(GLFWkeyfun key_callback) {
	glfwSetKeyCallback(window, key_callback);
}

void Window::SetMouseCallback(GLFWcursorposfun mouse_callback) {
	glfwSetCursorPosCallback(window, mouse_callback);
}

void Window::SetCursorPos(GLint xpos, GLint ypos) {
	glfwSetCursorPos(window, xpos, ypos);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}

bool Window::WindowShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::MakeContextCurrent() {
	glfwMakeContextCurrent(window);
}