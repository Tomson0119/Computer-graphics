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
	Object* curObj;

	float angle;
	float rotate;

	float orbit;
	float small_orbit;

	const float rotate_speed = 1.5f;
	const float move_dist = 0.08f;

	unsigned int polygon_mode;
	unsigned int example_scene;

public:
	Example();
	~Example();

	void init(int widow_w, int window_h);

	void draw();
	void key_event(unsigned char key, int x, int y);
	bool setTimer();

private:
	void sceneOne_draw();
	void sceneTwo_draw();

	void sceneOne_key_event(unsigned char key, int x, int y);
	void sceneTwo_key_event(unsigned char key, int x, int y);

private:
	glm::mat4 viewMat;
	glm::mat4 projMat;
};