#pragma once

#include "object.h"
#include "vertexarray.h"

class Line : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Line(const char* type);
	~Line() override;

	void setVertexArray() override;
	void draw() override;
};