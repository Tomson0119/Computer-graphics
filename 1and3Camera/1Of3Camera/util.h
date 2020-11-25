#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>


class Util
{
public:	
	Util();

	// Mathematics functions
	float getDistance(const glm::vec2& p1, const glm::vec2& p2);
	float getAngle(const glm::vec2& p1, const glm::vec2& p2);

	// Random float generator
	float generateFloat(float low, float high);

	// Convert function
	glm::vec2 convert_xy(int x, int y);
};