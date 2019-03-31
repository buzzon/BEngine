#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Message.h"

class Window
{
public:
	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void SetKeyCallback(GLFWkeyfun key_callback);
	void SwapBuffers();
	bool WindowShouldClose();

private:
	GLFWwindow* window;
	void MakeContextCurrent();
};

