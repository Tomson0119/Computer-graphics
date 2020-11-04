#include "rectangle.h"


Rect::Rect()
{
	const float hSize = 0.2f;

	{
		vertices.emplace_back(glm::vec3(-hSize, hSize, 0.0f));		
		vertices.emplace_back(glm::vec3(-hSize, -hSize, 0.0f));
		vertices.emplace_back(glm::vec3(hSize, -hSize, 0.0f));
		vertices.emplace_back(glm::vec3(hSize, hSize, 0.0f));

		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
		indices.emplace_back(0);
		indices.emplace_back(2);
		indices.emplace_back(3);
	}

	vertexArray = nullptr;
}

Rect::~Rect()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Rect::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals, indices);
}

void Rect::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
