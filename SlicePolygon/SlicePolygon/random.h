#pragma once

#include <glm/glm.hpp>

#include <ctime>

class Random
{
public:
	Random()
	{
		srand((unsigned int)time(0));
	}

	float generateFloat(float low, float high)
	{
		return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
	}

	glm::vec2 generateVec2(float low, float high)
	{
		float x = low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
		float y = low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));

		return glm::vec2(x, y);
	}
};