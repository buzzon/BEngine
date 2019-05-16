#pragma once

constexpr int glfw_ver_major = 3;
constexpr int glfw_ver_minor = 3;
#define GLEW_STATIC

#include "Window.h"
#include "FaceManager.h"
#include "Camera.h"

class b_engine
{
public:
	b_engine();
	~b_engine();

	enum win_size { height = 600, width = 800 };

	Window window{};
	camera camera;

	static void using_glew();
	void write_specifications() const; // ������� ����������� ��
	void calculate_delta_time(); // ��������� �������� deltaTime

	static void set_enables(GLenum cap, ...);
	FaceManager face_manager; // ��������� ���������� ������ 

	GLfloat get_delta_time() const; // ���������� �����, ��������� ����� ��������� � ������� ������
private:
	static int get_max_nr(); // ������ ������������ ���������� ������� ����������-������, ������������ � ������

	GLfloat delta_time_ = 0.0f;	// �����, ��������� ����� ��������� � ������� ������
	GLfloat last_frame_ = 0.0f;  	// ����� ������ ���������� �����
};
