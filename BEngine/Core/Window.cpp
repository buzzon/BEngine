#include "Window.h"

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
	}
}

// Set the required callback functions
void Window::SetKeyCallback(GLFWkeyfun key_callback)
{
	glfwSetKeyCallback(window, key_callback);
}

// Swap the screen buffers
void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

bool Window::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(window);
}

