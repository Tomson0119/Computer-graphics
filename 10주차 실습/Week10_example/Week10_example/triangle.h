#pragma once

#include "object.h"
#include "vertexarray.h"
#include "texture.h"

#include <string>

class Triangle : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoord;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;
	Texture* texture;

public:
	Triangle(const std::string& textureName);
	~Triangle() override;

	void draw(Shader* shader) override;
};