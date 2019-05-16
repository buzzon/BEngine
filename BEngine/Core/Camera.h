#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class camera
{
public:
	explicit camera(const glm::vec3& pos = glm::vec3(0.0f),
		GLfloat yaw = -90.0f,
		GLfloat pitch = 0.0f);

	struct axes
	{
		glm::vec3 right;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	};

	enum movement { forward, backward, left, right };

	glm::mat4 get_view_matrix() const;
	glm::mat4 get_projection_matrix(GLfloat aspect_ratio) const;
	glm::vec3 get_position() const;

	void rotate(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true);
	void move(movement direction, GLfloat delta_time);

	void set_hit_zoom(GLfloat value); // Устанавливает поле обзора
	void set_near_clipping_plane(GLfloat value); // Устанавливает ближнюю плоскость отсечения
	void set_far_clipping_plane(GLfloat value); // Устанавливает дальнюю плоскость отсечения
	void set_max_pitch(GLfloat value); //Устанавливает максимальный угол наклона

private:
	// Camera Attributes
	glm::vec3 position_;
	axes axes_;

	// Eular Angles
	GLfloat yaw_;
	GLfloat pitch_;
	GLfloat max_pitch_ = 89.0f;

	// Camera options
	GLfloat speed_ = 3.0f;
	GLfloat sensitivity_ = 0.05;
	GLfloat zoom_ = 45.0f;
	GLfloat near_clip_ = 0.1f;  // Ближняя плоскость отсечения
	GLfloat far_clip_ = 100.f; // Дальняя плоскость отсечения

	void update_vectors();
};

