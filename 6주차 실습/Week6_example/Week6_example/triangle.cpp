#include "triangle.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	vPos = new float[vNum];
	vColor = new float[vNum];	
	index = new unsigned int[iNum];

	for (unsigned int i = 0; i < vNum;i++)
	{
		vPos[i] = 0.0f;
		vColor[i] = 0.0f;
	}

	setPos(x1, y1, x2, y2, x3, y3);
	
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;

	setColor();

	vertexArray = nullptr;
}

void Triangle::setPos(float x1, float y1, float x2, float y2, float x3, float y3)
{
	vPos[0] = x1;
	vPos[1] = y1;
	vPos[3] = x2;
	vPos[4] = y2;
	vPos[6] = x3;
	vPos[7] = y3;
}

void Triangle::setColor()
{
	float color1 = (float)rand() / (float)RAND_MAX;
	float color2 = (float)rand() / (float)RAND_MAX;
	float color3 = (float)rand() / (float)RAND_MAX;

	vColor[0] = color1;
	vColor[1] = color2;
	vColor[2] = color3;
	vColor[3] = color1;
	vColor[4] = color2;
	vColor[5] = color3;
	vColor[6] = color1;
	vColor[7] = color2;
	vColor[8] = color3;	
}

void Triangle::setVertexArray()
{
	vertexArray = new VertexArray(vPos, vColor, index, vNum, iNum);
}

void Triangle::draw()
{
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, iNum, GL_UNSIGNED_INT, nullptr);
}

