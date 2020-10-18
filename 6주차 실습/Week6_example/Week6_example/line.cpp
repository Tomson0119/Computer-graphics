#include "line.h"

Line::Line(const char* type)
{
	if (type == "x")
	{
		vertices.emplace_back(glm::vec3(-10.0f, 0.0f, 0.5f));
		vertices.emplace_back(glm::vec3(10.0f, 0.0f, 0.5f));
	}
	else if (type == "y")
	{
		vertices.emplace_back(glm::vec3(0.0f, -1.0f, 0.5f));
		vertices.emplace_back(glm::vec3(0.0f, 1.0f, 0.5f));
	}
	else
	{
		vertices.emplace_back(glm::vec3(0.0f, 0.0f, -10.0f));
		vertices.emplace_back(glm::vec3(0.0f, 0.0f, 10.0f));
	}

	colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	colors.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices.emplace_back(0);
	indices.emplace_back(1);
	
	vertexArray = nullptr;
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
