#pragma once

#include "vertexarray.h"
#include "shader.h"

class Line
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	glm::mat4 worldTransform;

	VertexArray* vertexArray;

public:
	Line(const glm::vec2& vec);
	Line(const glm::vec2& begin, const glm::vec2& end);

	~Line();

	glm::vec2 getVertexBegin() { return vertices.at(0); }
	glm::vec2 getVertexEnd() { return vertices.at(1); }

	void changePos(const glm::vec2& pos);

	void setVertexArray();
	void draw(Shader* shader);
};