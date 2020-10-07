#pragma once

#include "shader.h"

class Triangles
{
private:
	float vPos[3][3];
	float vColor[3][3];

	GLint mode;

	const int data_size = 3;
	const float size = 0.2f;

	float pos_x, pos_y;
	float first_pos_y;
	float dx, dy;

	void convert_pos(int x, int y);
public:
	Triangles();
	Triangles(int x, int y);
	Triangles& operator=(const Triangles& other);

	float(*getPos())[3];
	float(*getColor())[3];

	void draw(GLint first, GLint count);
	void change_color();
	void change_pos();
	void change_mode(GLint mode);

	void boundary_check(float speed);
};
