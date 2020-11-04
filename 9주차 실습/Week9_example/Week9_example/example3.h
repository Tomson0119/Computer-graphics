#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>


class Example3
{
private:
	Shader* lightShader;
	Shader* lampShader;
	Camera* camera;

	std::vector<Object*> objs;
	std::vector<glm::vec2> poses;

	Object* light_bulb;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

	unsigned int polygon_mode;
	const int raindrops = 300;

	int REvent, SEvent;
	float move_y;

	int prev_time;

public:
	Example3(int window_w, int window_h);
	~Example3();

	void init();
	void draw();
	void key_event(unsigned char key, int x, int y);
	void setTimer();
};