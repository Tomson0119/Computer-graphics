#pragma once

#include "object.h"
#include "vertexarray.h"


class Rect : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Rect(const char* color);
	~Rect() override;

	void setVertexArray() override;
	void draw(Shader* shader) override;
};