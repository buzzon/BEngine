#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3
#define BName "BEngine"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>

class BEngine
{
public:
	BEngine();
	~BEngine();
	void Message(const char *message);
	void ErrorMessage(const char *message);
private:

};

