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
	std::vector<Poly*> pieces;
	std::vector<Line*> lines;

	Line* playerLine;

	unsigned int polygon_mode;

	int prev_time;
	int curr_time;
	int delta_time;

	bool collision_event(Poly* obj);
	void slice_polygon(Poly* obj, glm::vec2 points[]);

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