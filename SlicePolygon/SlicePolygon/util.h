#pragma once

#include "line.h"
#include "polygon.h"

#include <gl/freeglut.h>
#include <glm/glm.hpp>


class Util
{
public:
	Util();

	glm::vec2 getIntersectPoint2(const glm::vec2& v1, const glm::vec2& v2,
								 const glm::vec2& v3, const glm::vec2& v4);
	float generateFloat(float low, float high);
	glm::vec2 convert_xy(int x, int y);
};