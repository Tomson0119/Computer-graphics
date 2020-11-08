#pragma once

#include "vertexarray.h"
#include "shader.h"

class Poly
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	glm::vec2 pos;
	glm::mat4 worldTransform;

	VertexArray* vertexArray;

	bool FALL;
	
public:
	Poly();
	// For Rectangle
	Poly(const std::vector<glm::vec2>& container);

	~Poly();

	int getVerticesSize() { return static_cast<int>(vertices.size()); }
	
	glm::vec2 getVertex2(int index);

	void setFall() { FALL = true; }

	void translateWorld(float x, float y);
	void translateAlong(const glm::vec2& target, float speed);
	void setVertexArray();
	void draw(Shader* shader);
};