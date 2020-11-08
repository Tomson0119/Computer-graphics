#include "pyramid.h"


Pyramid::Pyramid()
{
	const float hSize = 0.2f;

	{
		vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f)); // 0
		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 2

		vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f)); // 0
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 4
		
		vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f)); // 0
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 3
		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1

		vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f)); // 0
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 4
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 3

		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 3
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 2

		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 3
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 4
	}

	{
		normals.emplace_back(glm::vec3(0.0f, 0.7071f, 0.7071f));
		normals.emplace_back(glm::vec3(0.0f, 0.7071f, 0.7071f));
		normals.emplace_back(glm::vec3(0.0f, 0.7071f, 0.7071f));

		normals.emplace_back(glm::vec3(0.7071f, 0.7071f, 0.0f));
		normals.emplace_back(glm::vec3(0.7071f, 0.7071f, 0.0f));
		normals.emplace_back(glm::vec3(0.7071f, 0.7071f, 0.0f));

		normals.emplace_back(glm::vec3(-0.7071f, 0.7071f, 0.0f));
		normals.emplace_back(glm::vec3(-0.7071f, 0.7071f, 0.0f));
		normals.emplace_back(glm::vec3(-0.7071f, 0.7071f, 0.0f));

		normals.emplace_back(glm::vec3(0.0f, 0.7071f, -0.7071f));
		normals.emplace_back(glm::vec3(0.0f, 0.7071f, -0.7071f));
		normals.emplace_back(glm::vec3(0.0f, 0.7071f, -0.7071f));

		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));

		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));

	}

	vertexArray = nullptr;
}

Pyramid::~Pyramid()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);

	delete vertexArray;
}

void Pyramid::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals);
}

void Pyramid::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
