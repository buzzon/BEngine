#pragma once

#include "INCLUDE_GL.h"

struct FaceManager
{
	enum Bypass { RIGHT = GL_CW, LEFT = GL_CCW };
	enum Face { BACK = GL_BACK, FRONT = GL_FRONT, ALL = GL_FRONT_AND_BACK };

	void ClippingFaces(Face face, Bypass bypass); // ��������� ������
	void DisableClippingFaces(); // ��������� ��������� ������, ���������� �� �����������
};

