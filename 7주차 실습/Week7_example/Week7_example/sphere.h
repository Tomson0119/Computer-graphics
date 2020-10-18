#pragma once

#include "object.h"
#include "vertexarray.h"

#include <vector>
#include <glm/glm.hpp>

class Sphere : public Object
{
private:
	const char* color;

public:
	Sphere(const char* color);
	~Sphere();

	VertexArray* vertexArray;

private:
	// member functions
	void buildVertices(const char *color);
	void clearArrays();
	void addVertex(float x, float y, float z);
	void addColor();
	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

	void setVertexArray() override;
	void draw(Shader* shader) override;

	// memeber vars
	const float radius = 0.5f;
	const unsigned int sectorCount = 36;                      // longitude, # of slices
	const unsigned int stackCount = 18;                         // latitude, # of stacks

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> indices;
};
