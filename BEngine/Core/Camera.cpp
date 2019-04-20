#include "Camera.h"

Camera::Camera(glm::vec3 pos, GLfloat yaw, GLfloat pitch)
{
	this->position = pos;
	this->yaw = yaw;
	this->pitch = pitch;

	this->updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->axes.front, this->axes.up);
}

glm::mat4 Camera::GetProjectionMatrix(GLfloat aspectRatio)
{
	return glm::perspective(this->zoom, aspectRatio, this->nearClip, this->farClip);
}

void Camera::Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= this->sensitivity;
	yoffset *= this->sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (constrainPitch)
	{
		this->pitch > this->maxPitch ? this->pitch = this->maxPitch : this->pitch;
		this->pitch < -this->maxPitch ? this->pitch = -this->maxPitch : this->pitch;
	}

	this->updateVectors();
}

void Camera::Move(Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->speed * deltaTime;
	if (direction == FORWARD)
		this->position += this->axes.front * velocity;
	if (direction == BACKWARD)
		this->position -= this->axes.front * velocity;
	if (direction == LEFT)
		this->position -= this->axes.right * velocity;
	if (direction == RIGHT)
		this->position += this->axes.right * velocity;
}

void Camera::SethitZoom(GLfloat value)
{
	this->zoom = value;
}

void Camera::SetNearClippingPlane(GLfloat value)
{
	this->nearClip = value;
}

void Camera::SetFarClippingPlane(GLfloat value)
{
	this->farClip = value;
}

void Camera::SetMaxPitch(GLfloat value)
{
	this->maxPitch = value;
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->axes.front = glm::normalize(front);
	this->axes.right = glm::normalize(glm::cross(this->axes.front, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->axes.up = glm::normalize(glm::cross(this->axes.right, this->axes.front));
}
