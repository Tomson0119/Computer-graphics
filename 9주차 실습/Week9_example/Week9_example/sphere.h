#pragma once

#include "object.h"
#include "vertexarray.h"

#include <vector>
#include <glm/glm.hpp>

class Sphere : public Object
{
public:
	Sphere();
	~Sphere();

	VertexArray* vertexArray;

private:
	// member functions
	void buildVertices();
	void clearArrays();
	void addVertex(float x, float y, float z);
	void addNormal(float x, float y, float z);
	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

	void setVertexArray() override;
	void draw(Shader* shader) override;

	// memeber vars
	const float radius = 0.5f;
	const unsigned int sectorCount = 36;                      // longitude, # of slices
	const unsigned int stackCount = 18;                         // latitude, # of stacks

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};
