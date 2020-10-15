#pragma once

#include "object.h"
#include "vertexarray.h"

class Pyramid : public Object
{
private:
	float* vPos;
	float* vColor;
	unsigned int* vIndex;

	const float hSize = 0.2f;

	const unsigned int vNum = 15;
	const unsigned int iNum = 18;

	VertexArray* vertexArray;

public:
	Pyramid();
	~Pyramid() override;

	void setVertexArray() override;
	void draw() override;
};