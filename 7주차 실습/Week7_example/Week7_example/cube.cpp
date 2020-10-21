#include "cube.h"


Cube::Cube(const char* color)
{
	const float hSize = 0.2f;

	{
		vertices.emplace_back(glm::vec3(-hSize, hSize, hSize));
		vertices.emplace_back(glm::vec3(-hSize, -hSize, hSize));
		vertices.emplace_back(glm::vec3(hSize, hSize, hSize));
		vertices.emplace_back(glm::vec3(hSize, -hSize, hSize));
		vertices.emplace_back(glm::vec3(-hSize, hSize, -hSize));
		vertices.emplace_back(glm::vec3(-hSize, -hSize, -hSize));
		vertices.emplace_back(glm::vec3(hSize, hSize, -hSize));
		vertices.emplace_back(glm::vec3(hSize, -hSize, -hSize));
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (color == "red")
			colors.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
		else if (color == "blue")
			colors.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
		else if (color == "green")
			colors.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
		else if (color == "yellow")
			colors.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
		else if (color == "purple")
			colors.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f));
		else if (color == "sky")
			colors.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
		else
			colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	}


	unsigned int vIndex[]
	{
		0, 1, 3,
		0, 3, 2,
		0, 2, 4,
		4, 2, 6,
		2, 3, 7,
		2, 7, 6,
		0, 4, 5,
		0, 5, 1,
		4, 6, 7,
		4, 7, 5,
		1, 5, 3,
		3, 5, 7
	};

	for (unsigned int i = 0; i < sizeof(vIndex) / sizeof(*vIndex); i++)
		indices.emplace_back(vIndex[i]);

	vertexArray = nullptr;
}

Cube::~Cube()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(colors);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Cube::setVertexArray()
{
	vertexArray = new VertexArray(vertices, colors, indices);
}

void Cube::draw(Shader* shader)
{
	shader->setWorldTransform(getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
