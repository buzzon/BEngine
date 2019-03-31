#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Message.h"
#include "Window.h"

// удалить
#include <SOIL/SOIL.h>

class BEngine
{
public:
	BEngine();
	~BEngine();

	enum WinSize { HEIGHT = 600, WIDTH = 800 };

	ShaderProgram shaderProgram;
	Window window;

	void UsingGlew();
	void WriteSpecifications(); // Вывести возможности ПК
private:
	int GetMaxNR(); // Узнать максимальное количество входных переменных-вершин, передаваемых в шейдер
};

