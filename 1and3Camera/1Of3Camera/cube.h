#pragma once

#include "object.h"
#include "vertexarray.h"


class Cube : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

	glm::vec3 color;

public:
	Cube(float r, float g, float b);
	~Cube() override;

	void draw(Shader* shader) override;
};