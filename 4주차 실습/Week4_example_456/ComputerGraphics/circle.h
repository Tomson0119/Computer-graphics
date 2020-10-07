#pragma once

#include "shader.h"

class Circle
{
private:
	float vPos[100][3];
	float vColor[100][3];

	const int vNum = 100;
	const int data_size = 3;
	const double PI = 3.141592;

	float radius;
	float pos_x, pos_y;

	GLint mode;

	void convert_pos(int x, int y);

public:
	Circle(GLint mode);
	Circle(int x, int y, GLint mode);
	Circle& operator=(const Circle& other);

	void draw();
	void setColor();
	void setPos();
	
	void setRadius(float value) { radius = value; }
	float getRadius() const { return radius; }

	float(*getPos())[3] { return vPos; }
	float(*getColor())[3] { return vColor; }

	int getNum() const { return vNum; }
};