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
	void write_specifications() const; // Вывести возможности ПК
	void calculate_delta_time(); // Вычислить значение deltaTime

	static void set_enables(GLenum cap, ...);
	FaceManager face_manager; // Управляет отсечением граней 

	GLfloat get_delta_time() const; // Возвращает время, прошедшее между последним и текущим кадром
private:
	static int get_max_nr(); // Узнать максимальное количество входных переменных-вершин, передаваемых в шейдер

	GLfloat delta_time_ = 0.0f;	// Время, прошедшее между последним и текущим кадром
	GLfloat last_frame_ = 0.0f;  	// Время вывода последнего кадра
};
