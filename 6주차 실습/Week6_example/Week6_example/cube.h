#pragma once

#include "object.h"
#include "vertexarray.h"

class Cube : public Object
{
private:
	float* vPos;
	float* vColor;
	unsigned int* vIndex;

	const float hSize = 0.2f;

	const unsigned int vNum = 24;
	const unsigned int iNum = 36;

	VertexArray* vertexArray;

public:
	Cube();
	~Cube();

	void setVertexArray() override;
	void draw() override;
};