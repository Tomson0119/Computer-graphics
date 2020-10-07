#include "triangles.h"

Triangles::Triangles()
{
	for (int i = 0; i < data_size; i++)
	{
		for (int j = 0; j < data_size; j++)
		{
			vPos[i][j] = 0.0f;
			vColor[i][j] = 0.0f;
		}
	}

	dx = 0.0;
	dy = 0.0;

	pos_x = 0.0;
	pos_y = 0.0;
	first_pos_y = 0.0;

	mode = GL_TRIANGLES;
}

Triangles::Triangles(int x, int y)
{
	*this = Triangles();

	convert_pos(x, y);

	first_pos_y = pos_y;

	change_pos();
	change_color();
}

Triangles& Triangles::operator=(const Triangles& other)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->vPos[i][j] = other.vPos[i][j];
			this->vColor[i][j] = other.vColor[i][j];
		}
	}

	this->pos_x = other.pos_x;
	this->pos_y = other.pos_y;
	
	this->first_pos_y = other.first_pos_y;
	this->dx = other.dx;
	this->dy = other.dy;
	this->mode = other.mode;

	return *this;
}

void Triangles::convert_pos(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	width = width / 2;
	height = height / 2;

	pos_x = (float)(x - width) / (float)width;
	pos_y = (float)(height - y) / (float)height;
}

float(*Triangles::getPos())[3]
{
	return vPos;
}

float(*Triangles::getColor())[3]
{
	return vColor;
}

void Triangles::draw(GLint first, GLint count)
{
	glDrawArrays(mode, first, count);
}

void Triangles::change_color()
{
	for (int i = 0; i < 3; i++)
	{
		vColor[0][i] = (float)rand() / (float)RAND_MAX;
	}

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vColor[i][j] = vColor[0][j];
		}
	}
}

void Triangles::change_pos()
{
	pos_x += dx;
	pos_y += dy;

	vPos[0][0] = pos_x - size;
	vPos[0][1] = pos_y - size;
	vPos[0][2] = 0.0;

	vPos[1][0] = pos_x;
	vPos[1][1] = pos_y + size;
	vPos[1][2] = 0.0;

	vPos[2][0] = pos_x + size;
	vPos[2][1] = pos_y - size;
	vPos[2][2] = 0.0;
}

void Triangles::change_mode(GLint mode)
{
	this->mode = mode;
}

void Triangles::boundary_check(float speed)
{
	float bound = 1.0f - size;
	if (pos_x > bound && dx > 0.0f)
	{
		pos_x = bound;
		dx = 0.0f;
		dy = speed;
	}
	else if (pos_y > bound && dy > 0.0f)
	{
		pos_y = bound;
		dx = -speed;
		dy = 0.0f;
	}
	else if (pos_x < -bound && dx < 0.0f)
	{
		pos_x = -bound;
		dx = 0.0f;
		dy = -speed;
	}
	else if (pos_y < first_pos_y && dy < 0.0f)
	{
		pos_y = first_pos_y;
		dx = speed;
		dy = 0.0f;
	}
	else if (pos_y == first_pos_y
		&& pos_x < bound && pos_x > -bound)
	{
		dx = speed;
		dy = 0.0f;
	}
}