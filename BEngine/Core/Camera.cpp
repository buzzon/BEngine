#include "Camera.h"

Camera::Camera(glm::vec3 pos, GLfloat yaw, GLfloat pitch)
{
	this->position = pos;
	this->front = FRONT;
	this->up = UP;

	this->yaw = yaw;
	this->pitch = pitch;
	this->maxPitch = MAX_PITCH;

	this->speed = SPEED;
	this->sensitivity = SENSITIVTY;
	this->zoom = ZOOM;
	this->nearClip = NEAR_CLIP;
	this->farClip = FAR_CLIP;

	this->updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
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

void Camera::Move(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->speed * deltaTime;
	if (direction == FORWARD)
		this->position += this->front * velocity;
	if (direction == BACKWARD)
		this->position -= this->front * velocity;
	if (direction == LEFT)
		this->position -= this->right * velocity;
	if (direction == RIGHT)
		this->position += this->right * velocity;
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, UP)); 
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
