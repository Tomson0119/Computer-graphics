#include "line.h"

#include <cmath>

Line::Line(const char* type)
{
	vertexArray = nullptr;

	if (type == "x" || type == "y" || type == "z") {
		if (type == "x")
		{
			vertices.emplace_back(glm::vec3(-0.5f, 0.0f, 0.0f));
			vertices.emplace_back(glm::vec3(0.5f, 0.0f, 0.0f));
		}
		else if (type == "y")
		{
			vertices.emplace_back(glm::vec3(0.0f, -0.5f, 0.0f));
			vertices.emplace_back(glm::vec3(0.0f, 0.5f, 0.0f));
		}
		else
		{
			vertices.emplace_back(glm::vec3(0.0f, 0.0f, -0.5f));
			vertices.emplace_back(glm::vec3(0.0f, 0.0f, 0.5f));
		}

		colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
		colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

		indices.emplace_back(0);
		indices.emplace_back(1);
	}
	else if (type == "circle")
	{
		int vertCount = 50;
		float radius = 1.0f;
		float angle = 0.0f;

		for (int i = 0; i < vertCount; i++)
		{
			angle = 2.0 * 3.141592 * i / vertCount;
			vertices.emplace_back(glm::vec3(radius * cosf(angle), 0.0f, radius * sinf(angle)));
			colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
			indices.emplace_back(i);
		}
	}
	
}

Line::~Line()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(colors);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Line::setVertexArray()
{
	vertexArray = new VertexArray(vertices, colors, indices);
}

void Line::draw(Shader* shader)
{
	shader->setWorldTransform(getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_LINE_LOOP, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
