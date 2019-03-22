#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Message.h"

// удалить
#include <SOIL/SOIL.h>

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
	int GetMaxNR(); // Узнать максимальное количество входных переменных-вершин, передаваемых в шейдер
private:
};

