#include "rectangle.h"

Rect::Rect()
{
	vPos = new float[data_size];
	vColor = new float[data_size];

	for (int i = 0; i < data_size; i++)
	{
		*(vPos + i) = 0.0f;
		*(vColor + i) = 0.0f;
	}

	vPos[0] = -width;
	vPos[1] = height;
	vPos[3] = -width;
	vPos[4] = -height;
	vPos[6] = width;
	vPos[7] = -height;
	vPos[9] = width;
	vPos[10] = height;
}

void Rect::draw()
{
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}