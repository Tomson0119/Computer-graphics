#include "pyramid.h"


Pyramid::Pyramid()
{
	const float hSize = 0.2f;

	vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f));
	vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize));
	vertices.emplace_back(glm::vec3(hSize, -hSize, hSize));
	vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize));
	vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize));

	colors.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));

	unsigned int vIndex[]
	{
		0, 1, 2,
		0, 2, 4,
		0, 3, 1,
		0, 4, 3,
		1, 3, 2,
		2, 3, 4
	};

	for (unsigned int i = 0; i < sizeof(vIndex) / sizeof(*vIndex); i++)
		indices.emplace_back(vIndex[i]);

	vertexArray = nullptr;
}

Pyramid::~Pyramid()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(colors);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Pyramid::setVertexArray()
{
	vertexArray = new VertexArray(vertices, colors, indices);
}

void Pyramid::draw()
{
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
