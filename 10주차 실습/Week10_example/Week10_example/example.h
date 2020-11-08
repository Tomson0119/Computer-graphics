#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>


class Example
{
private:
	Shader* shader;
	Camera* camera;

	Object* background;

	std::vector<Object*> cube;
	std::vector<Object*> pyramid;

	glm::vec3 lightPos;

	unsigned int polygon_mode;

	bool isCube;
	float angle_y;
	float angle_x;

public:
	Example(int window_w, int window_h);
	~Example();

	void init();
	void draw();
	void key_event(unsigned char key, int x, int y);
	void setTimer();
};