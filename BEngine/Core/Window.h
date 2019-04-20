#pragma once

#include "INCLUDE_GL.h"

#include "Message.h"

class Window
{
public:
	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void SetKeyCallback(GLFWkeyfun key_callback);
	void SetMouseCallback(GLFWcursorposfun mouse_callback);


	void SetCursorPos(GLint xpos, GLint ypos); // Устанавливает курсор в позицию x y
	void SwapBuffers(); // Заменяет буферы экрана
	bool WindowShouldClose(); // Проверяет закрыто ди окно

private:
	GLFWwindow* window;
	void MakeContextCurrent();
};

