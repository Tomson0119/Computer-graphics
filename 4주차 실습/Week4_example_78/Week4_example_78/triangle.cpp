#include "triangle.h"

Triangle::Triangle()
{
	vPos = new float[data_size];
	vColor = new float[data_size];

	for (int i = 0; i < data_size; i++)
	{
		*(vPos + i) = 0.0f;
		*(vColor + i) = 0.0f;
	}
	pos_x = 0.0f;
	pos_y = 0.0f;

	first_x = 0.0f;
	first_y = 0.0f;

	dx = speed;
	dy = speed;

	direction = "down";
}

Triangle::Triangle(int x, int y)
	: Triangle()
{
	convert_pos(x, y);

	first_x = pos_x;
	first_y = pos_y;

	setPos();
	setColor();
}

void Triangle::convert_pos(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	pos_x = (float)(x - width / 2) / (float)(width / 2);
	pos_y = (float)(height / 2 - y) / (float)(height / 2);
}

void Triangle::setColor()
{
	float color1 = (float)rand() / (float)RAND_MAX;
	float color2 = (float)rand() / (float)RAND_MAX;
	float color3 = (float)rand() / (float)RAND_MAX;

	for (int i = 0; i < data_size / 3; i++)
	{
		*(vColor + i * 3) = color1;
		*(vColor + i * 3 + 1) = color2;
		*(vColor + i * 3 + 2) = color3;
	}
}

void Triangle::setPos()
{
	if (direction == "right")
	{
		vPos[0] = pos_x - size * 2;
		vPos[1] = pos_y;
		vPos[3] = pos_x + size;
		vPos[4] = pos_y - size;
		vPos[6] = pos_x + size;
		vPos[7] = pos_y + size;
	}
	else if (direction == "left")
	{
		vPos[0] = pos_x + size * 2;
		vPos[1] = pos_y;
		vPos[3] = pos_x - size;
		vPos[4] = pos_y + size;
		vPos[6] = pos_x - size;
		vPos[7] = pos_y - size;
	}
	else if (direction == "up")
	{
		vPos[0] = pos_x;
		vPos[1] = pos_y - size * 2;
		vPos[3] = pos_x + size;
		vPos[4] = pos_y + size;
		vPos[6] = pos_x - size;
		vPos[7] = pos_y + size;
	}
	else if (direction == "down")
	{
		vPos[0] = pos_x;
		vPos[1] = pos_y + size * 2;
		vPos[3] = pos_x - size;
		vPos[4] = pos_y - size;
		vPos[6] = pos_x + size;
		vPos[7] = pos_y - size;
	}
}

void Triangle::change_direction(Rect rect)
{
	float x = rect.getWidth();
	float y = rect.getHeight();

	for (int i = 0; i < data_size / 3; i++)
	{
		if (*(vPos + i * 3) >= 1.0f ||
			( *(vPos + i * 3) >= -x && *(vPos + i * 3) <= -x + 0.03f 
				&& *(vPos + i * 3 + 1) >= -y && *(vPos + i * 3 + 1) <= y))
		{
			if (first_x <= x && first_x >= -x && first_y <= y && first_y >= -y)
				direction = "left";
			else
				direction = "right";
			dx *= -1;
			return;
		}
		if (*(vPos + i * 3) <= -1.0f ||
			(*(vPos + i * 3) <= x && *(vPos + i * 3) >= x - 0.03f 
				&& *(vPos + i * 3 + 1) >= -y && *(vPos + i * 3 + 1) <= y))
		{
			if (first_x <= x && first_x >= -x && first_y <= y && first_y >= -y)
				direction = "right";
			else
				direction = "left";
			dx *= -1;
			return;
		}
		if (*(vPos + i * 3 + 1) >= 1.0f ||
			(*(vPos + i * 3 + 1) >= -y && *(vPos + i * 3 + 1) <= -y + 0.03f
				&& *(vPos + i * 3) >= -x && *(vPos + i * 3) <= x))
		{
			if (first_x <= x && first_x >= -x && first_y <= y && first_y >= -y)
				direction = "down";
			else
				direction = "up";
			dy *= -1;
			return;
		}
		if (*(vPos + i * 3 + 1) <= -1.0f ||
			*(vPos + i * 3 + 1) <= y && *(vPos + i * 3 + 1) >= y - 0.03f
			&& *(vPos + i * 3) >= -x && *(vPos + i * 3) <= x)
		{
			if (first_x <= x && first_x >= -x && first_y <= y && first_y >= -y)
				direction = "up";
			else
				direction = "down";
			dy *= -1;
			return;
		}
	}
}

void Triangle::setAnimation(Rect rect)
{
	change_direction(rect);

	pos_x += dx;
	pos_y += dy;
	setPos();
}

void Triangle::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
