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
	void WriteSpecifications(); // ������� ����������� ��
	void CalculateDeltaTime(); // ��������� �������� deltaTime

	void SetEnables(GLenum cap, ...);
	FaceManager faceManager; // ��������� ���������� ������ 

	GLfloat GetDeltaTime(); // ���������� �����, ��������� ����� ��������� � ������� ������
private:
	int GetMaxNR(); // ������ ������������ ���������� ������� ����������-������, ������������ � ������

	GLfloat deltaTime = 0.0f;	// �����, ��������� ����� ��������� � ������� ������
	GLfloat lastFrame = 0.0f;  	// ����� ������ ���������� �����
};

