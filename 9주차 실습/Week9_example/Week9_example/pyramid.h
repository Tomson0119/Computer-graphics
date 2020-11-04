#pragma once

#include "object.h"
#include "vertexarray.h"

class Pyramid : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	VertexArray* vertexArray;

public:
	Pyramid();
	~Pyramid() override;

	void setVertexArray() override;
	void draw(Shader* shader) override;
};