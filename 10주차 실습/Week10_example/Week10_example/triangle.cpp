#include "triangle.h"


Triangle::Triangle(const std::string& textureName)
{
	const float hSize = 0.4f;
	{
		vertices.emplace_back(glm::vec3(0.0f, hSize, -hSize));
		vertices.emplace_back(glm::vec3(-hSize, -hSize, 0.0f));
		vertices.emplace_back(glm::vec3(hSize, -hSize, 0.0f));
		
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		texCoord.emplace_back(glm::vec2(0.5f, 1.0f));
		texCoord.emplace_back(glm::vec2(0.0f, 0.0f));
		texCoord.emplace_back(glm::vec2(1.0f, 0.0f));

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
	}	

	vertexArray = new VertexArray(vertices, normals, texCoord, indices);
	texture = new Texture(textureName);
}

Triangle::~Triangle()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<glm::vec2>().swap(texCoord);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
	delete texture;
}

void Triangle::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	texture->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
