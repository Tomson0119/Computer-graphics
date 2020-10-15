#include "cube.h"


Cube::Cube()
{
	vPos = new float[vNum]
	{
		-hSize,  hSize,  hSize,
		-hSize, -hSize,  hSize,
		 hSize,  hSize,  hSize,
		 hSize, -hSize,  hSize,
		-hSize,  hSize, -hSize,
		-hSize, -hSize, -hSize,
		 hSize,  hSize, -hSize,
		 hSize, -hSize, -hSize
	};

	vColor = new float[vNum]
	{
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	vIndex = new unsigned int[iNum]
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

	vertexArray = nullptr;
}

Cube::~Cube()
{
	delete vPos;
	delete vColor;
	delete vIndex;
	delete vertexArray;
}

void Cube::setVertexArray()
{
	vertexArray = new VertexArray(vPos, vColor, vIndex, vNum, iNum);
}

void Cube::draw()
{
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, iNum, GL_UNSIGNED_INT, nullptr);
}
