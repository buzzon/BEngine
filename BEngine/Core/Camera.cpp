#include "Camera.h"


void Camera::UpdateProjection()
{
	this->projection = glm::perspective( 
		glm::radians(FoV),
		attitudeOfParties,
		nearClippingPlane, 
		farClippingPlane
	);
}

void Camera::SetFoV(float value)
{
	this->FoV = value;
	this->UpdateProjection();
}

void Camera::SetattitudeOfParties(float value)
{
	this->attitudeOfParties = value;
	this->UpdateProjection();
}

void Camera::SetnearClippingPlane(float value)
{
	this->nearClippingPlane = value;
	this->UpdateProjection();
}

void Camera::SetfarClippingPlane(float value)
{
	this->farClippingPlane = value;
	this->UpdateProjection();
}

void Camera::UpdateDirection()
{
	this->direction.x = cos(verticalAngle) * sin(horizontalAngle);
	this->direction.y = sin(verticalAngle);
	this->direction.z = direction.x;
}

void Camera::UpdateRight()
{
	this->right.x = sin(horizontalAngle - 1.57f);
	this->right.y = 0;
	this->right.z = cos(horizontalAngle - 1.57f);
}

void Camera::UpdateFullDirection()
{
	this->UpdateRight();
	this->UpdateDirection();
	this->up = glm::cross(right, direction);
}

Camera::Camera(glm::vec3 pos, float horizontalAngle, float verticalAngle)
{
	this->position = pos;
	this->horizontalAngle = horizontalAngle;
	this->verticalAngle = verticalAngle;
}

Camera::~Camera()
{
}
