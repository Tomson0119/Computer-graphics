#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"
#include "line.h"

#include <vector>


class Example
{
private:
	Shader* shader;
	Camera* camera;

	std::vector<Object*> objs;
	Line* line;

	unsigned int polygon_mode;
	bool animation;

	int prev_time;

	glm::vec2 begin;
	glm::vec2 temp;
	glm::vec2 end;

	glm::vec2 convert_xy(int x, int y);

public:
	Example(int window_w, int window_h);
	~Example();

	void init();

	void draw();
	void key_event(unsigned char key, int x, int y);
	void mouse_event(int button, int state, int x, int y);
	void motion_event(int x, int y);
	void setTimer();
};