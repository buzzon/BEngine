#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void SetKeyCallback(GLFWkeyfun key_callback);
	void SetMouseCallback(GLFWcursorposfun mouse_callback);


	void SetCursorPos(GLint xpos, GLint ypos); // ������������� ������ � ������� x y
	void SwapBuffers(); // �������� ������ ������
	bool WindowShouldClose(); // ��������� ������� �� ����

private:
	GLFWwindow* window;
	void MakeContextCurrent();
};

