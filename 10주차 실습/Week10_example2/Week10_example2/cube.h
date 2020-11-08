#pragma once

#include "object.h"
#include "vertexarray.h"


class Cube : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Cube();
	~Cube() override;

	void setVertexArray() override;
	void draw(Shader* shader) override;
};