#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3
#define GLEW_STATIC
#include "INCLUDE_GL.h"

#include "ShaderProgram.h"
#include "Texture.h"
#include "Message.h"
#include "Window.h"
#include "FaceManager.h"
#include "Camera.h"

class BEngine
{
public:
	BEngine();
	~BEngine();

	enum WinSize { HEIGHT = 600, WIDTH = 800 };

	Window window;
	Camera camera;

	void UsingGlew();
	void WriteSpecifications(); // Вывести возможности ПК
	void CalculateDeltaTime(); // Вычислить значение deltaTime

	void SetEnables(GLenum cap, ...);
	FaceManager faceManager; // Управляет отсечением граней 

	GLfloat GetDeltaTime(); // Возвращает время, прошедшее между последним и текущим кадром
private:
	int GetMaxNR(); // Узнать максимальное количество входных переменных-вершин, передаваемых в шейдер

	GLfloat deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
	GLfloat lastFrame = 0.0f;  	// Время вывода последнего кадра
};

