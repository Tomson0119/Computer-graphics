#pragma once

#include <vector>

#include "shader.h"
#include "object.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


class Example
{
private:
	Shader* shader;
	std::vector<Object*> objs;
	
	float door;
	float door_move;
	float robot;
	float robot_rotate;

	float move_x;
	float move_y;
	float move_z;
	float jump;
	float amount;
	float way;

	float angle;

	int camera_turn;

	float animation;
	float increase;
	float turning;

	float bench;
	float bench_rotate;
	float bench_bar;
	float bench_bar_amount;

	bool trigger;

	unsigned int polygon_mode;
	unsigned int window_w;
	unsigned int window_h;

	const float move_dist = 0.01f;
public:
	Example();
	~Example();

	void init(int window_w, int window_h);

	void draw();
	void key_event(unsigned char key, int x, int y);
	bool setTimer();

private:
	void print_location();

private:
	struct Camera
	{
		glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Position = glm::vec3(0.0f, 0.2f, 2.5f);
	};

	Camera camera = Camera();

	glm::mat4 globalMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;
};