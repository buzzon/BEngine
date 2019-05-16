#include "Camera.h"

camera::camera(const glm::vec3& pos, const GLfloat yaw, const GLfloat pitch)
{
	this->position_ = pos;
	this->yaw_ = yaw;
	this->pitch_ = pitch;

	this->update_vectors();
}

glm::mat4 camera::get_view_matrix() const
{
	return glm::lookAt(this->position_, this->position_ + this->axes_.front, this->axes_.up);
}

glm::mat4 camera::get_projection_matrix(const GLfloat aspect_ratio) const
{
	return glm::perspective(this->zoom_, aspect_ratio, this->near_clip_, this->far_clip_);
}

glm::vec3 camera::get_position() const
{
	return position_;
}

void camera::rotate(GLfloat x_offset, GLfloat y_offset, const GLboolean constrain_pitch)
{
	x_offset *= this->sensitivity_;
	y_offset *= this->sensitivity_;

	this->yaw_ += x_offset;
	this->pitch_ += y_offset;

	if (constrain_pitch)
	{
		this->pitch_ > this->max_pitch_ ? this->pitch_ = this->max_pitch_ : this->pitch_;
		this->pitch_ < -this->max_pitch_ ? this->pitch_ = -this->max_pitch_ : this->pitch_;
	}

	this->update_vectors();
}

void camera::move(const movement direction, const GLfloat delta_time)
{
	const auto velocity = this->speed_ * delta_time;
	if (direction == forward)
		this->position_ += this->axes_.front * velocity;
	if (direction == backward)
		this->position_ -= this->axes_.front * velocity;
	if (direction == left)
		this->position_ -= this->axes_.right * velocity;
	if (direction == right)
		this->position_ += this->axes_.right * velocity;
}

void camera::set_hit_zoom(const GLfloat value)
{
	this->zoom_ = value;
}

void camera::set_near_clipping_plane(const GLfloat value)
{
	this->near_clip_ = value;
}

void camera::set_far_clipping_plane(const GLfloat value)
{
	this->far_clip_ = value;
}

void camera::set_max_pitch(const GLfloat value)
{
	this->max_pitch_ = value;
}

void camera::update_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw_)) * cos(glm::radians(this->pitch_));
	front.y = sin(glm::radians(this->pitch_));
	front.z = sin(glm::radians(this->yaw_)) * cos(glm::radians(this->pitch_));

	this->axes_.front = glm::normalize(front);
	this->axes_.right = glm::normalize(glm::cross(this->axes_.front, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->axes_.up = glm::normalize(glm::cross(this->axes_.right, this->axes_.front));
}
