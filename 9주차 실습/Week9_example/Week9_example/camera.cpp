#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int window_w, int window_h)
{
	Direction = glm::vec3(0.0f, 0.0f, 0.1f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Position = glm::vec3(0.0f, 0.2f, 4.0f);

	aspect = (float)window_w / (float)window_h;
	viewMat = glm::lookAt(Position, Direction, Up);
	projMat = glm::perspective(glm::radians(fovy),
		aspect, N, F);
}

Camera::~Camera()
{
}
