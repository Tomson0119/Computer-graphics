#pragma once

#include "object.h"
#include "vertexarray.h"

class Line : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;

public:
	Line(const glm::vec2& vec);
	Line(const glm::vec2& begin, const glm::vec2& end);

	~Line() override;

	void changePos(const glm::vec2& pos);

	void setVertexArray() override;
	void draw(Shader* shader) override;
};