#pragma once

#include "INCLUDE_GL.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat MAX_PITCH = 89.0f;

const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.05;

const GLfloat ZOOM = 45.0f;
const GLfloat NEAR_CLIP = 0.1f; // Ближняя плоскость отсечения
const GLfloat FAR_CLIP = 100.f; // Дальняя плоскость отсечения

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f),
		GLfloat yaw = YAW,
		GLfloat pitch = PITCH);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(GLfloat aspectRatio);

	void Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void Move(Camera_Movement direction, GLfloat deltaTime);

	//void SethitZoom(GLfloat value); // Устанавливает поле обзора
	//void SetNearClippingPlane(GLfloat value); // Устанавливает ближнюю плоскость отсечения
	//void SetFarClippingPlane(GLfloat value); // Устанавливает дальнюю плоскость отсечения
	//void SetAspectRatio(GLfloat value); // Устанавливает соотношение сторон
	//void SetMaxPitch(GLfloat value); //Устанавливает максимальный угол наклона

private:
	// Camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;
	GLfloat maxPitch;

	// Camera options
	GLfloat speed;
	GLfloat sensitivity;
	GLfloat zoom;
	GLfloat nearClip; // Ближняя плоскость отсечения
	GLfloat farClip; // Дальняя плоскость отсечения
	//GLfloat aspectRatio; // Отношение сторон

	void updateVectors();
};

