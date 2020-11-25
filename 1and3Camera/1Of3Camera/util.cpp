#include "util.h"

#include <iostream>
#include <ctime>
#include <cmath>

Util::Util()
{
	srand((unsigned int)time(0));
}

float Util::getDistance(const glm::vec2& p1, const glm::vec2& p2)
{
	float ret = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	return ret;
}

float Util::getAngle(const glm::vec2& p1, const glm::vec2& p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;

	float angle = atan2(dy, dx) * 180.0f / static_cast<float>(3.141592);

	if (angle < 0.0f) angle *= -1.0f;
	if (dy <= 0.0f) angle += 90.0f;
	if (dx <= 0.0f) angle = 90.0f - angle;

	if (dy > -0.01f && dy < 0.01f) {
		angle = (dx > 0) ? 90.0f : -90.0f;
	}
	if (dx > -0.01f && dx < 0.01f) {
		angle = (dy > 0) ? 0.0f : 180.0f;
	}
	return angle;
}

float Util::generateFloat(float low, float high)
{
	return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
}

glm::vec2 Util::convert_xy(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	float pos_x = static_cast<float>(x - width / 2) /
		static_cast<float>(width / 2);

	float pos_y = static_cast<float>(height / 2 - y) /
		static_cast<float>(height / 2);

	return glm::vec2(pos_x, pos_y);
}