#include "circle.h"

Circle::Circle(GLint mode)
{
	for (int i = 0; i < vNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vPos[i][j] = 0.0f;
			vColor[i][j] = 0.0f;
		}
	}

	pos_x = 0.0;
	pos_y = 0.0;
	radius = 0.1f;

	this->mode = mode;
}

Circle::Circle(int x, int y, GLint mode)
	: Circle(mode)
{
	convert_pos(x, y);

	setPos();
	setColor();
}

Circle& Circle::operator=(const Circle& other)
{
	for (int i = 0; i < vNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->vPos[i][j] = other.vPos[i][j];
			this->vColor[i][j] = other.vColor[i][j];
		}
	}

	this->pos_x = other.pos_x;
	this->pos_y = other.pos_y;
	this->radius = other.radius;

	return *this;
}

void Circle::convert_pos(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int height = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	pos_x = (float)(x - width) / (float)width;
	pos_y = (float)(height - y) / (float)height;
}

void Circle::draw()
{
	glDrawArrays(mode, 0, vNum);
}

void Circle::setColor()
{
	float color1 = (float)rand() / (float)RAND_MAX;
	float color2 = (float)rand() / (float)RAND_MAX;
	float color3 = (float)rand() / (float)RAND_MAX;

	for (int i = 0; i < vNum; i++)
	{
		vColor[i][0] = color1;
		vColor[i][1] = color2;
		vColor[i][2] = color3;
	}
}

void Circle::setPos()
{
	int j = 0;

	for (int i = 0; i < vNum; i++)
	{
		j = (j + 1) % vNum;
		double deg = PI * 2.0 / (double)vNum * (double)j;

		vPos[i][0] = radius * (float)cos(deg) + pos_x;
		vPos[i][1] = radius * (float)sin(deg) + pos_y;
	}
}