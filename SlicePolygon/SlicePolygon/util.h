#pragma once

#include "line.h"
#include "polygon.h"

#include <gl/freeglut.h>
#include <glm/glm.hpp>


class Util
{
private:
	float ccw(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3);
public:
	Util();

	bool isIntersection(Line* line1, Line* line2);
	glm::vec2 getIntersectPoint2(Line *line1, Line* line2);
	float generateFloat(float low, float high);
	glm::vec2 convert_xy(int x, int y);
};