#include "util.h"

#include <iostream>
#include <ctime>

Util::Util()
{
	srand((unsigned int)time(0));
}

glm::vec2 Util::getIntersectPoint2(const glm::vec2& v1, const glm::vec2& v2,
								   const glm::vec2& v3, const glm::vec2& v4)
{
	float increase1, constant1, sameValue1;
	float increase2, constant2, sameValue2;

	// Line 1
	if (v1.x == v2.x)
		sameValue1 = v1.x;
	else {
		increase1 = static_cast<float>((v2.y - v1.y) / (v2.x - v1.x));
		constant1 = v1.y - increase1 * v1.x;
	}

	// Line 2
	if (v3.x == v4.x)
		sameValue2 = v3.x;
	else {
		increase2 = static_cast<float>((v4.y - v3.y) / (v4.x - v3.x));
		constant2 = v3.y - increase2 * v3.x;
	}

	// IntersectPoint
	glm::vec2 point;
	if (v1.x == v2.x && v3.x == v4.x) return glm::vec2(-100.0f);
	if (v1.x == v2.x)
		point = glm::vec2(sameValue1, increase2 * sameValue1 + constant2);
	else if (v3.x == v4.x)
		point = glm::vec2(sameValue2, increase1 * sameValue2 + constant1);
	else {
		point.x = -(constant1 - constant2) / (increase1 - increase2);
		point.y = increase1 * point.x + constant1;
	}
	return point;
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