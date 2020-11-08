#pragma once

#include "object.h"
#include "vertexarray.h"

class Line : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoord;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Line(const char* type);
	~Line() override;

	void draw(Shader* shader) override;
};