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
	struct Position
	{
		float pos_x, pos_y;
		bool active;

		void set(float x, float y)
		{
			pos_x = x;
			pos_y = y;
			active = false;
		}
	};
	Position poses[24];

	Shader* shader;
	Camera* camera;
	Util* util;

	std::vector<Poly*> objs;
	std::vector<Line*> lines;
	std::vector<Line*> net;

	// For debug
	std::vector<Line*> temp;

	Poly* captured;
	Line* playerLine;	

	unsigned int polygon_mode;
	bool showLine;
	float move_speed;
	

	int prev_time;
	int curr_time;
	int delta_time;


	// Slice collision functions
	bool collision_event(Poly* obj);
	void slice_polygon(Poly* obj, glm::vec2 points[]);

	// Net collision functions
	int isInside(glm::vec2 position, bool checkActive);

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