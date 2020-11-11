#pragma once

#include "vertexarray.h"
#include "shader.h"

class Poly
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	glm::vec2 first_pos;
	glm::vec2 pos;
	glm::mat4 worldTransform;

	VertexArray* vertexArray;

	float min_x, max_x;
	float min_y, max_y;
	
public:
	Poly();
	// For Rectangle
	Poly(const std::vector<glm::vec2>& container);

	~Poly();

	void setPos(glm::vec2 vec) { pos = vec; }

	int getVerticesSize() { return static_cast<int>(vertices.size()); }
	glm::vec2 getPos() { return pos; }
	glm::vec2 getVertex2(int index);

	void scaleWorld(float x, float y);
	void translateWorld(float x, float y);
	void translateAlong(const glm::vec2& target, float speed);
	void setVertexArray();
	void draw(Shader* shader);

	bool FIXED = false;
	bool FALL = false;
	bool RIGHT = false;
};