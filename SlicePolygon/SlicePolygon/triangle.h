#pragma once

#include "object.h"
#include "vertexarray.h"


class Triangle : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Triangle();
	~Triangle() override;

	void setVertexArray() override;
	void draw(Shader* shader) override;
};