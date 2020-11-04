#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 Direction;
	glm::vec3 Up;
	glm::vec3 Position;

	glm::mat4 viewMat;
	glm::mat4 projMat;

	const float fovy = 45.0f;
	const float N = 0.1f;
	const float F = 50.f;

	float aspect;

public:
	Camera(int window_w, int window_h);
	~Camera();

	glm::mat4 getViewMat() { return viewMat; }
	glm::mat4 getProjMat() { return projMat; }
	
	glm::vec3 getPosition() { return Position; }

	void translateCameraPos(float x, float y, float z);
	void rotateCameraCenter(float angle, float x, float y, float z);
	void rotateCameraPos(float angle, float x, float y, float z);
};