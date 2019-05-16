#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window
{
public:
	void create_window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void set_key_callback(GLFWkeyfun key_callback) const;
	void set_mouse_callback(GLFWcursorposfun mouse_callback) const;

	void set_cursor_pos(GLint x_pos, GLint y_pos) const; // ������������� ������ � ������� x y
	void swap_buffers() const; // �������� ������ ������
	bool window_should_close() const; // ��������� ������� �� ����

private:
	GLFWwindow* window_ = nullptr;
	void make_context_current() const;
};

