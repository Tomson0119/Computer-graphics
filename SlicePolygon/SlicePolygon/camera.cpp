#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

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

void Camera::translateCameraPos(float x, float y, float z)
{
	Position = Position + glm::vec3(x, y, z);
	viewMat = glm::lookAt(Position, Direction, Up);
}

void Camera::rotateCameraCenter(float angle, float x, float y, float z)
{
	Direction -= Position;
	Direction = glm::rotate(Direction, glm::radians(angle), glm::vec3(x, y, z));
	Direction += Position;
	viewMat = glm::lookAt(Position, Direction, Up);
}
