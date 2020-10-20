#include "triangle.h"


Triangle::Triangle(const char* color)
{
	const float hSize = 0.2f;

	{
		vertices.emplace_back(glm::vec3(0.0f, hSize, 0.0f));
		vertices.emplace_back(glm::vec3(-hSize, -hSize, 0.0f));
		vertices.emplace_back(glm::vec3(hSize, -hSize, 0.0f));
		
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

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
	}	

	vertexArray = nullptr;
}

Triangle::~Triangle()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(colors);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Triangle::setVertexArray()
{
	vertexArray = new VertexArray(vertices, colors, indices);
}

void Triangle::draw(Shader* shader)
{
	shader->setWorldTransform(getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
