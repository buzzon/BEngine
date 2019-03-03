#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3
#define BName "BEngine"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <cstdlib> 
#include <stdexcept>

class BEngine
{
public:
	BEngine();
	~BEngine();

	GLFWwindow* window;
	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void UsingGlew();
private:
	void Message(const char *message);
	void ErrorMessage(const char *message);
	void CauseExeption(const char *message);
};

