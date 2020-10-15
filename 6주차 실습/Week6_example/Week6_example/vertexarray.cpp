#include "vertexarray.h"

#include <iostream>


VertexArray::VertexArray(float* vPos, float* vColor, unsigned int* vIndex,
	unsigned int vSize, unsigned int iSize)
{
	VAO = 0;
	VBO[0] = NULL;
	VBO[1] = NULL;
	IBO = NULL;

	set_buffer(vPos, vColor, vIndex, vSize, iSize);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::set_buffer(float* vPos, float* vColor, unsigned int *vIndex,
	unsigned int vSize, unsigned int iSize)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(unsigned int), vIndex, GL_STATIC_DRAW);

}

void VertexArray::setActive()
{
	glBindVertexArray(VAO);
}
