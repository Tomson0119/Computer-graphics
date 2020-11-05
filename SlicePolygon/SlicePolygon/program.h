#pragma once

#include "shader.h"
#include "camera.h"
#include "random.h"

#include "object.h"
#include "line.h"

#include <vector>


class Program
{
private:
	Shader* shader;
	Camera* camera;
	Random* random;

	std::vector<Object*> objs;
	std::vector<Line*> lines;
	Line* playerLine;

	unsigned int polygon_mode;
	bool animation;

	int prev_time;

	

	glm::vec2 convert_xy(int x, int y);

public:
	Program(int window_w, int window_h);
	~Program();

	void init();

	void draw();
	void key_event(unsigned char key, int x, int y);
	void mouse_event(int button, int state, int x, int y);
	void motion_event(int x, int y);
	void setTimer();
};