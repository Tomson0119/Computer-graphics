#include "polygon.h"


Poly::Poly()
{
	glm::vec2 tri[4][3] = {
		{ glm::vec2(0.0f,  0.15f), glm::vec2(-0.15f, -0.15f), glm::vec2(0.15f, -0.15f) },
		{ glm::vec2(-0.2f,  0.05f), glm::vec2(0.10f, -0.15f), glm::vec2(0.10f,  0.13f) },
		{ glm::vec2(-0.1f,  0.10f), glm::vec2(-0.13f, -0.20f), glm::vec2(0.14f,  0.00f) },
		{ glm::vec2(0.21f, 0.13f), glm::vec2(-0.13f, -0.10f), glm::vec2(0.13f, -0.10f) }
	};

	glm::vec2 rect[4][4] = {
		{ glm::vec2(-0.15f, 0.15f), glm::vec2(-0.16f, -0.15f), glm::vec2(0.14f, -0.14f), glm::vec2(0.15f, 0.16f) },
		{ glm::vec2(-0.12f, 0.13f), glm::vec2(-0.15f, -0.15f), glm::vec2(0.18f, -0.15f), glm::vec2(0.11f, 0.13f) },
		{ glm::vec2(-0.15f, 0.10f), glm::vec2(-0.13f, -0.15f), glm::vec2(0.23f, -0.10f), glm::vec2(0.10f, 0.20f) },
		{ glm::vec2(-0.20f, 0.00f), glm::vec2(-0.05f, -0.19f), glm::vec2(0.22f,  0.00f), glm::vec2(-0.05f, 0.17f) }
	};

	{
		int rectangle = rand() % 2;
		int index = rand() % 4;

		if (rectangle) {
			vertices.emplace_back(glm::vec3(rect[index][0], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][1], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][2], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][3], 0.0f));
		}
		else {
			vertices.emplace_back(glm::vec3(tri[index][0], 0.0f));
			vertices.emplace_back(glm::vec3(tri[index][1], 0.0f));
			vertices.emplace_back(glm::vec3(tri[index][2], 0.0f));
		}

		for (unsigned int i = 0; i < vertices.size(); i++)
			normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
		if (rectangle) {
			indices.emplace_back(0);
			indices.emplace_back(2);
			indices.emplace_back(3);
		}
	}

	setVertexArray();
}

Poly::~Poly()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Poly::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals, indices);
}

void Poly::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
