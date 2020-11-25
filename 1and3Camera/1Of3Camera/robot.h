#pragma once

#include "object.h"

#include <vector>
#include <glm/glm.hpp>

class Robot
{
private:
	std::vector<Object*> objs;

	glm::mat4 outWorld;

	float angle_all;
	float angle_arm;
	float increse_arm;
	float face;
	float gap;

	glm::vec3 pos;
	glm::vec3 firstPos;

public:
	Robot();
	~Robot();

	glm::vec3 getPos() { return pos; }
	glm::vec3 getBehindPos();

	void setPlayer();

	void setFirstPos(const glm::vec3& first) { firstPos = first; }
	void translateAlong(const glm::vec2& target, float speed);
	void reset();

	void translateWorld(const glm::vec3& vec);
	void translateWorld(float x, float y, float z);
	void rotateAroundCenter(float angle);
	void rotateDirection(float angle);

	void setTimer();
	void draw(class Shader* shader);	
};