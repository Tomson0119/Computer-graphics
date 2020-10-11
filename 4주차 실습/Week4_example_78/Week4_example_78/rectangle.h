#pragma once

#include "util.h"

class Rect
{
private:
	float* vPos;
	float* vColor;

	const int data_size = 12;

	const float width = 0.5f;
	const float height = 0.5f;

public:
	Rect();

	void draw();

	float getWidth() { return width; }
	float getHeight() { return height; }
	int getDataSize() { return data_size; }

	float* getPos() { return vPos; }
	float* getColor() { return vColor; }
};