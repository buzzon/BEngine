#pragma once

#define GLFWVERMAJOR 3
#define GLFWVERMINOR 3
#define GLEW_STATIC

#include "ShaderProgram.h"
#include "Texture.h"
#include "Message.h"
#include "Window.h"

// �������
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
	void WriteSpecifications(); // ������� ����������� ��
	void CalculateNewDeltaTime(); // ��������� ����� �������� deltaTime
	GLfloat GetDeltaTime();
private:
	int GetMaxNR(); // ������ ������������ ���������� ������� ����������-������, ������������ � ������

	GLfloat deltaTime = 0.0f;	// �����, ��������� ����� ��������� � ������� ������
	GLfloat lastFrame = 0.0f;  	// ����� ������ ���������� �����
};

