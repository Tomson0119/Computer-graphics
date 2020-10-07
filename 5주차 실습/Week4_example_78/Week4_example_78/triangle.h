#pragma once

#include "rectangle.h"

class Triangle
{
private:
	float* vPos;
	float* vColor;
	
	float first_x, first_y;
	float pos_x, pos_y;
	float dx, dy;

	std::string direction;

	const int data_size = 9;	
	const float size = 0.07f;
	const float speed = 0.02f;

	void convert_pos(int x, int y);

	void setPos();
	void setColor();

	void change_direction(Rect rect);

public:
	Triangle();
	Triangle(int x, int y);

	void draw();

	void setAnimation(Rect rect);
	

	float* getPos() const { return vPos; }
	float* getColor() const { return vColor; }

	int getDataSize() { return data_size; }
};