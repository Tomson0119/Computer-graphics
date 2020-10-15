#pragma once

#include <vector>

#include "object.h"
#include "vertexarray.h"

class Sphere : public Object
{
private:
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<unsigned int> indices;

	const unsigned int sectors = 36;
	const unsigned int stacks = 18;
	const float radius = 0.5f;

	VertexArray* vertexArray;
public:
	Sphere();
	~Sphere() override;

	void setVertexArray() override;
	void draw() override;
};
