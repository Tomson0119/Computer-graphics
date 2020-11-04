#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>


class Example2
{
private:
	Shader* lightShader;
	Shader* lampShader;
	Camera* camera;

	std::vector<Object*> crane;
	Object* light_bulb;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

	unsigned int polygon_mode;

	int REvent;
	int BEvent;
	int NEvent;
	int TEvent;
	bool GEvent;

	float move_x;

	int prev_time;

public:
	Example2(int window_w, int window_h);
	~Example2();

	void init();
	void draw();
	void key_event(unsigned char key, int x, int y);
	void setTimer();
};