#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
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

void Camera::firstPointView(const glm::vec3& pos,float face)
{
	float x = pos.x, z = pos.z;

	if (face == 0.0f)
		z += 2.0f;
	else if (face == -90.0f)
		x += -2.0f;
	else if (face == 90.0f)
		x += 2.0f;
	else if (face == 180.0f)
		z += -2.0f;

	else if (face == 45.0f || face == -45.0f)
	{
		x += sinf(face) * 5.0f;
		z += cosf(face) * 5.0f;
	}
	else
	{
		if (face == 135.0f) x += 2.0f;
		else if (face == -135) x += -2.0f;
		z += cosf(face) * 5.0f;
	}

	Position = pos;
	Direction = glm::vec3(x, pos.y - 0.5f, z);
	viewMat = glm::lookAt(Position, Direction, Up);
}

void Camera::thirdPointView()
{
	Direction = glm::vec3(0.0f, 0.0f, 0.1f);
	Position = glm::vec3(0.0f, 1.2f, 4.5f);
	viewMat = glm::lookAt(Position, Direction, Up);
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

void Camera::rotateCameraPos(float angle, float x, float y, float z)
{
	Position = glm::rotate(Position, glm::radians(angle), glm::vec3(x, y, z));
	viewMat = glm::lookAt(Position, Direction, Up);
}