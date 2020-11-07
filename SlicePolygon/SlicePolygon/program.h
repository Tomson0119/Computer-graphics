#pragma once

#include "shader.h"
#include "camera.h"
#include "util.h"

#include "polygon.h"
#include "line.h"

#include <vector>


class Program
{
private:
	Shader* shader;
	Camera* camera;
	Util* util;

	std::vector<Poly*> objs;
	std::vector<Line*> lines;
	std::vector<Poly*> boxes;

	Line* playerLine;

	unsigned int polygon_mode;
	bool animation;
	int prev_time;

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