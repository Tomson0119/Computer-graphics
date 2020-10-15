#include "pyramid.h"


Pyramid::Pyramid()
{
	vPos = new float[vNum]
	{
		 0.0f,   hSize,  0.0f,
		-hSize, -hSize,  hSize,
		 hSize, -hSize,  hSize,
		-hSize, -hSize, -hSize,
		 hSize, -hSize, -hSize
	};

	vColor = new float[vNum]
	{
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	vIndex = new unsigned int[iNum]
	{
		0, 1, 2,
		0, 2, 4,
		0, 3, 1,
		0, 4, 3,
		1, 3, 2,
		2, 3, 4
	};

	vertexArray = nullptr;
}

Pyramid::~Pyramid()
{
	delete vPos;
	delete vColor;
	delete vIndex;
	delete vertexArray;
}

void Pyramid::setVertexArray()
{
	vertexArray = new VertexArray(vPos, vColor, vIndex, vNum, iNum);
}

void Pyramid::draw()
{
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, iNum, GL_UNSIGNED_INT, nullptr);
}
