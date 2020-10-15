#pragma once

#include <gl/glew.h>

class VertexArray
{
private:
	GLuint VAO;
	GLuint VBO[2];
	GLuint IBO;

public:
	VertexArray(float* vPos, float* vColor, unsigned int* vIndex,
		unsigned int vSize, unsigned int iSize);
	~VertexArray();

	void setActive();

private:
	void set_buffer(float* vPos, float* vColor, unsigned int* vIndex,
		unsigned int vSize, unsigned int iSize);
};