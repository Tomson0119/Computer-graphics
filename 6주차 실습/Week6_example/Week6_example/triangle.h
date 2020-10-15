#pragma once

#include "vertexarray.h"

#include <cstdlib>
#include <ctime>

class Triangle
{
private:
	float* vPos;
	float* vColor;

	unsigned int* index;

	const unsigned int vNum = 9;
	const unsigned int iNum = 3;

	void setPos(float x1, float y1, float x2, float y2, float x3, float y3);
	void setColor();

	VertexArray* vertexArray;

public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3);

	void setVertexArray();
	void draw();
};