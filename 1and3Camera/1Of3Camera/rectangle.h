#pragma once

#include "object.h"
#include "vertexarray.h"
#include "texture.h"

#include <string>

class Rect : public Object
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoord;
	std::vector<unsigned int> indices;

	VertexArray* vertexArray;
	Texture* texture;

public:
	Rect(const std::string& textureName);
	~Rect() override;

	void draw(Shader* shader) override;
};