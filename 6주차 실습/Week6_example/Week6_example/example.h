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
	std::vector<Line*> lines;
	std::vector<Object*> objs;

	glm::mat4 transformMat;

	float angle_x;
	float angle_y;

	float rotate_x;
	float rotate_y;

	const float rotate_speed = 5.0f;

	unsigned int polygon_mode;

public:
	Example();
	~Example();

	void init();

	void draw();
	void key_event(unsigned char key, int x, int y);
	void mouse_event(int button, int state, int x, int y);
	bool setTimer();

private:
	void init_shader();
	void init_vertexArray();
};