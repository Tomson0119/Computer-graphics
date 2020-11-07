#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>

#include <ctime>

class Util
{
public:
	Util()
	{
		srand((unsigned int)time(0));
	}

	float generateFloat(float low, float high)
	{
		return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
	}

	glm::vec2 convert_xy(int x, int y)
	{
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		float pos_x = static_cast<float>(x - width / 2) /
			static_cast<float>(width / 2);

		float pos_y = static_cast<float>(height / 2 - y) /
			static_cast<float>(height / 2);

		return glm::vec2(pos_x, pos_y);
	}
};