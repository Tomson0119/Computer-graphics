#include "line.h"

Line::Line(const char* type)
{
	if (type == "x")
	{
		vertices.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));
		vertices.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (type == "y")
	{
		vertices.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f));
		vertices.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		vertices.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
		vertices.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
	}

	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices.emplace_back(0);
	indices.emplace_back(1);
	
	vertexArray = new VertexArray(vertices, normals, indices);
}

Line::~Line()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<glm::vec2>().swap(texCoord);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Line::draw(Shader* shader)
{
	shader->setMat4("world", getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_LINE_LOOP, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
