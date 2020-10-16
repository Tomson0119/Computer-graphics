#pragma once

#include <vector>

#include "shader.h"
#include "object.h"
#include "line.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


class Example
{
private:
	Shader* shader;
	std::vector<Object*> objs;
	Object* curObj;

	float angle_x;
	float angle_y;

	float cube_y; // For example_scene 2
	float pyramid_y; // For example_scene 2

	float rotate_x;
	float rotate_y;

	float move_x;
	float move_y;

	const float rotate_speed = 2.5f;
	const float move_dist = 0.02f;

	const unsigned int WHOLE = 0;
	const unsigned int CUBE = 1;
	const unsigned int PYRAMID = 2;

	unsigned int rotate_mode; // For example_scene 2
	unsigned int polygon_mode;
	unsigned int example_scene;

public:
	Example();
	~Example();

	void init();

	void draw();
	void key_event(unsigned char key, int x, int y);
	void special_key(int key, int x, int y);
	void mouse_event(int button, int state, int x, int y);
	
	bool setTimer();

private:
	void init_shader();
	void init_vertexArray();

	void sceneOne_draw();
	void sceneTwo_draw();

	void sceneOne_key_event(unsigned char key, int x, int y);
	void sceneTwo_key_event(unsigned char key, int x, int y);
};