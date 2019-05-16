#pragma once
#include <GL/glew.h>

struct face_manager
{
	enum bypass { right = GL_CW, left = GL_CCW };
	enum face { back = GL_BACK, front = GL_FRONT, all = GL_FRONT_AND_BACK };

	static void clipping_faces(face face, bypass bypass); // Отсечение граней
	static void disable_clipping_faces(); // Выключает отсечение граней, отвернутых от наблюдателя
};

