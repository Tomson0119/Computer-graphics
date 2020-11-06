#include "rectangle.h"


Rect::Rect()
{
	const float hSize = 0.2f;

	glm::vec2 vertex[4][4] = {
		{ glm::vec2(-0.15f, 0.15f), glm::vec2(-0.16f, -0.15f), glm::vec2(0.14f, -0.14f), glm::vec2( 0.15f, 0.16f) },
		{ glm::vec2(-0.12f, 0.13f), glm::vec2(-0.15f, -0.15f), glm::vec2(0.18f, -0.15f), glm::vec2( 0.11f, 0.13f) },
		{ glm::vec2(-0.15f, 0.10f), glm::vec2(-0.13f, -0.15f), glm::vec2(0.23f, -0.10f), glm::vec2( 0.10f, 0.20f) },
		{ glm::vec2(-0.20f, 0.00f), glm::vec2(-0.05f, -0.19f), glm::vec2(0.22f,  0.00f), glm::vec2(-0.05f, 0.17f) }
	};

	{
		int index = rand() % 4;

		vertices.emplace_back(glm::vec3(vertex[index][0], 0.0f));		
		vertices.emplace_back(glm::vec3(vertex[index][1], 0.0f));
		vertices.emplace_back(glm::vec3(vertex[index][2], 0.0f));
		vertices.emplace_back(glm::vec3(vertex[index][3], 0.0f));

		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
		indices.emplace_back(0);
		indices.emplace_back(2);
		indices.emplace_back(3);
	}

	setVertexArray();
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
