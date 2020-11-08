#pragma once

#include "object.h"
#include "vertexarray.h"


class Rect : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Rect();
	~Rect() override;

	void setVertexArray() override;
	void draw(Shader* shader) override;
};