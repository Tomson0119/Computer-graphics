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
	Line(float x1, float y1, float x2, float y2);

	~Line();

	glm::vec2 getPoint1() { return vertices.at(0); }
	glm::vec2 getPoint2() { return vertices.at(1); }

	void changePos(const glm::vec2& pos);

	void setVertexArray();
	void draw(Shader* shader);
};