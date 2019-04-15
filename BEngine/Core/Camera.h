#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	void SetFoV(float value); // Устанавливает поле обзора
	void SetattitudeOfParties(float value); // Устанавливает отношение сторон
	void SetnearClippingPlane(float value); // Устанавливает ближнюю плоскость отсечения
	void SetfarClippingPlane(float value); // Устанавливает дальнюю плоскость отсечения

	void UpdateFullDirection(); // Обновляет направление камеры

	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
			float horizontalAngle = 0.0f,
			float verticalAngle = 0.0f);

protected:
	glm::vec3 position; // Позиция камеры
	float horizontalAngle; // Горизонтальный угол
	float verticalAngle; // Вертикальный угол

private:
	float speed = 3.0f; // Скорость перемещения камеры
	float sensitivity = 0.05f; // Чувствительность мыши

	glm::mat4 projection;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	float FoV; // Поле обзора
	float attitudeOfParties = 16.0f / 9.0f; // Отношение сторон
	float nearClippingPlane = 0.1f; // Ближняя плоскость отсечения
	float farClippingPlane = 100.f; // Дальняя плоскость отсечения

	void UpdateProjection();
	void UpdateDirection();
	void UpdateRight();
};

