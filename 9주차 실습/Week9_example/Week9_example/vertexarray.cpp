#include "vertexarray.h"

#include <iostream>


VertexArray::VertexArray(const std::vector<glm::vec3>& vertices,
						 const std::vector<glm::vec3>& normals,
						 const std::vector<unsigned int>& indices)
{
	VAO = 0;
	VBO[0] = NULL;
	VBO[1] = NULL;
	IBO = NULL;

	set_buffer(vertices, normals, indices);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::set_buffer(const std::vector<glm::vec3>& vertices,
							 const std::vector<glm::vec3>& normals,
							 const std::vector<unsigned int>& indices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

}

void VertexArray::setActive()
{
	glBindVertexArray(VAO);
}
