#include "cube.h"


Cube::Cube()
{
	const float hSize = 0.2f;

	{
		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize)); // 0
		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 3

		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize)); // 0
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 3
		vertices.emplace_back(glm::vec3(hSize, hSize, hSize)); // 2

		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize)); // 0
		vertices.emplace_back(glm::vec3(hSize, hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize)); // 4

		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize)); // 4
		vertices.emplace_back(glm::vec3(hSize, hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(hSize, hSize, -hSize)); // 6

		vertices.emplace_back(glm::vec3(hSize, hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 3
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 7

		vertices.emplace_back(glm::vec3(hSize, hSize, hSize)); // 2
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 7
		vertices.emplace_back(glm::vec3(hSize, hSize, -hSize)); // 6

		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize)); // 0
		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize)); // 4
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 5

		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize)); // 0
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 5
		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1

		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize)); // 4
		vertices.emplace_back(glm::vec3(hSize, hSize, -hSize)); // 6
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 7

		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize)); // 4
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 7
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 5

		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize)); // 1
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 5
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 3

		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize)); // 3
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize)); // 5
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize)); // 7
	}

	{
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));

		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));

		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));

		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));

		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));

		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));
		normals.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));

		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));

		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
		normals.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));

		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
	
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		normals.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
	}

	vertexArray = nullptr;
}

Cube::~Cube()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Cube::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals);
}

void Cube::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
