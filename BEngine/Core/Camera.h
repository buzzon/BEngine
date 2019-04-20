#pragma once

#include "INCLUDE_GL.h"

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f),
		GLfloat yaw = -90.0f,
		GLfloat pitch = 0.0f);

	struct Axes
	{
		glm::vec3 right;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	};

	enum Movement { FORWARD, BACKWARD, LEFT, RIGHT };

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(GLfloat aspectRatio);

	void Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void Move(Movement direction, GLfloat deltaTime);

	void SethitZoom(GLfloat value); // Устанавливает поле обзора
	void SetNearClippingPlane(GLfloat value); // Устанавливает ближнюю плоскость отсечения
	void SetFarClippingPlane(GLfloat value); // Устанавливает дальнюю плоскость отсечения
	void SetMaxPitch(GLfloat value); //Устанавливает максимальный угол наклона

private:
	// Camera Attributes
	glm::vec3 position;
	Axes axes;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;
	GLfloat maxPitch = 89.0f;

	// Camera options
	GLfloat speed = 3.0f;
	GLfloat sensitivity = 0.05;
	GLfloat zoom = 45.0f;
	GLfloat nearClip = 0.1f;  // Ближняя плоскость отсечения
	GLfloat farClip = 100.f; // Дальняя плоскость отсечения

	void updateVectors();
};

