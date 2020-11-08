#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>


class Example
{
private:
	Shader* lightShader;
	Shader* lampShader;
	Shader* blendShader;

	Camera* camera;

	std::vector<Object*> objs;
	std::vector<glm::vec2> poses;

	Object* cube;
	Object* light_bulb;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

	unsigned int polygon_mode;
	const int raindrops = 300;

	int REvent, SEvent;
	float move_y;

	int prev_time;

public:
	Example(int window_w, int window_h);
	~Example();

	void init();
	void draw();
	void key_event(unsigned char key, int x, int y);
	void setTimer();
};