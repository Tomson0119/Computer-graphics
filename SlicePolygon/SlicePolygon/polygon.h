#pragma once

#include "vertexarray.h"
#include "shader.h"

class Poly
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	glm::mat4 worldTransform;
	glm::vec2 pos;

	VertexArray* vertexArray;

	
public:
	Poly();
	Poly(const glm::vec4 vec);

	~Poly();

	int getVerticesSize() { return static_cast<int>(vertices.size()); }
	
	glm::vec2 getVertex2(int index);
	glm::vec4 getBoundBox();

	void translateWorld(float x, float y);
	void translateAlong(const glm::vec2& target, float speed);
	void setVertexArray();
	void draw(Shader* shader);
};