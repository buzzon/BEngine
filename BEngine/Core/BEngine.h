#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3
#define BName "BEngine"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>


#include <stdio.h>
#include <cstdlib> 
#include <stdexcept>

#include "ShaderProgram.h"

class BEngine
{
public:
	BEngine();
	~BEngine();

	GLFWwindow* window;
	ShaderProgram shaderProgram;
	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void UsingGlew();

	void WriteSpecifications(); // Вывести возможности ПК
	int GetMaxNR(); //Узнать максимальное количество входных переменных-вершин, передаваемых в шейдер
private:
	void Message(const char *message);
	void ErrorMessage(const char *message);
	void CauseExeption(const char *message);
};

