#include "triangle.h"

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3, const char* direction)
{
	vPos = new float[vNum];
	vColor = new float[vNum];	

	for (int i = 0; i < vNum;i++)
	{
		vPos[i] = 0.0f;
		vColor[i] = 0.0f;
	}

	setPos(x1, y1, x2, y2, x3, y3);

	first_x = x2;
	first_y = y2;

	setColor(direction);
	
	move_value = speed;
	scale_value = speed;

	mode = GL_TRIANGLES;
	motion = false;

	move_x = 0.0f;
	move_y = 0.0f;
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

void Triangle::setColor(const char* direction)
{
	if (direction == "up" || direction == "down" 
		|| direction == "left" || direction == "right")
	{
		float color1 = (float)rand() / (float)RAND_MAX;
		float color2 = (float)rand() / (float)RAND_MAX;
		float color3 = (float)rand() / (float)RAND_MAX;

		vColor[3] = color1;
		vColor[4] = color2;
		vColor[5] = color3;
		vColor[6] = color1;
		vColor[7] = color2;
		vColor[8] = color3;

		this->direction = direction;
	}
	else if (direction == "blue")
	{
		vColor[2] = 1.0f;
		vColor[5] = 1.0f;
		vColor[8] = 1.0f;
	}
	else if (direction == "green")
	{
		vColor[1] = 1.0f;
		vColor[4] = 1.0f;
		vColor[7] = 1.0f;
	}
	else if (direction == "red")
	{
		vColor[0] = 1.0f;
		vColor[3] = 1.0f;
		vColor[6] = 1.0f;
	}
	else if (direction == "yellow")
	{
		vColor[0] = 1.0f;
		vColor[1] = 1.0f;
		vColor[3] = 1.0f;
		vColor[4] = 1.0f;
		vColor[6] = 1.0f;
		vColor[7] = 1.0f;
	}	
}

void Triangle::convert_xy(int x, int y, float& new_x, float& new_y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	new_x = (float)(x - width / 2) / (float)(width / 2);
	new_y = (float)(height / 2 - y) / (float)(height / 2);
}

bool Triangle::check_line()
{
	if ((vPos[0] == vPos[3] && vPos[1] == vPos[4]) ||
		(vPos[0] == vPos[6] && vPos[1] == vPos[7]) ||
		(vPos[3] == vPos[6] && vPos[4] == vPos[7]))
		return true;
	else
		return false;
}

void Triangle::draw()
{
	if (check_line())
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	else
		glDrawArrays(mode, 0, 3);
}

void Triangle::move()
{	
	if (direction == "left")
	{
		if (vPos[3] > first_x || vPos[3] <= -1.0f) move_value *= -1;
		vPos[0] += -move_value;
		vPos[3] += -move_value;
		vPos[6] += -move_value;
	}
	else if (direction == "right")
	{
		if (vPos[3] < first_x || vPos[3] >= 1.0f) move_value *= -1;
		vPos[0] += move_value;
		vPos[3] += move_value;
		vPos[6] += move_value;
	}
	else if (direction == "up")
	{
		if (vPos[4] < first_y || vPos[4] >= 1.0f) move_value *= -1;
		vPos[1] += move_value / 1.4f;
		vPos[4] += move_value / 1.4f;
		vPos[7] += move_value / 1.4f;
	}
	else if (direction == "down")
	{
		if (vPos[4] > first_y || vPos[4] <= -1.0f) move_value *= -1;
		vPos[1] += -move_value / 1.4f;
		vPos[4] += -move_value / 1.4f;
		vPos[7] += -move_value / 1.4f;
	}
}

void Triangle::scale()
{
	if (direction == "left")
	{
		if (vPos[4] > first_y || vPos[4] <= vPos[1] + 0.01f) 
			scale_value *= -1;
		vPos[4] += -scale_value;
		vPos[7] += scale_value;
	}
	else if (direction == "right")
	{
		if (vPos[4] < first_y || vPos[4] >= vPos[1] + 0.01f) scale_value *= -1;
		vPos[4] += scale_value;
		vPos[7] += -scale_value;
	}
	else if (direction == "up")
	{
		if (vPos[3] > first_x || vPos[3] <= vPos[0] + 0.01f) scale_value *= -1;
		vPos[3] += -scale_value;
		vPos[6] += scale_value;
	}
	else if (direction == "down")
	{
		if (vPos[3] < first_x || vPos[3] >= vPos[0] + 0.01f) scale_value *= -1;
		vPos[3] += scale_value;
		vPos[6] += -scale_value;
	}	
}

void Triangle::line_to_triangle(float bound)
{
	if (vPos[1] > vPos[7] + speed) vPos[1] -= speed;
	if (vPos[3] > bound + speed) vPos[3] -= speed;
}

void Triangle::tri_to_rect(float min_x, float max_x, int toggle)
{
	if(vPos[0] > min_x + speed) vPos[0] -= speed;
	if (toggle == 1 && vPos[6] < max_x - speed) vPos[6] += speed;
}

void Triangle::rect_to_pent(float bound_x,float bound_y, int toggle)
{
	if (toggle == 1) {
		if (vPos[4] > bound_y) vPos[4] -= speed;
		if (vPos[6] < bound_x) vPos[6] += speed;
	}
	else if (toggle == 2)
	{
		if (vPos[3] < bound_x) vPos[3] += speed;
		if (vPos[6] > 2.0 * vPos[0] - bound_x) vPos[6] -= speed;
	}
	else if (toggle == 3)
	{
		if (vPos[3] > 2.0 * vPos[0] - bound_x) vPos[3] -= speed;
		if (vPos[7] > bound_y) vPos[7] -= speed;
	}
}

void Triangle::pent_to_point(float pos_x, float pos_y)
{
	float bound = 0.03f;
	for (int i = 0; i < vNum / 3; i++)
	{
		if (vPos[i * 3] < pos_x - bound) vPos[i * 3] += speed;
		else if (vPos[i * 3] > pos_x + bound) vPos[i * 3] -= speed;
		
		if (vPos[i * 3 + 1] > pos_y + bound) vPos[i * 3 + 1] -= speed;
		else if (vPos[i * 3 + 1] < pos_y - bound) vPos[i * 3 + 1] += speed;
	}
}

void Triangle::change_mode(GLint mode)
{
	this->mode = mode;
}

void Triangle::setMotion(int x,int y)
{
	float new_x, new_y;
	convert_xy(x, y, new_x, new_y);

	for (int i = 0; i < vNum / 3; i++)
	{
		if (vPos[i * 3] >= new_x - 0.01f && vPos[i * 3] <= new_x + 0.01f
			&& vPos[i * 3 + 1] >= new_y - 0.01f && vPos[i * 3 + 1] <= new_y + 0.01f)
		{
			motion = true;
			move_x = vPos[i * 3];
			move_y = vPos[i * 3 + 1];
			return;
		}
	}
	move_x = 0.0f;
	move_y = 0.0f;
	motion = false;	
}

void Triangle::move_vertex_by_mouse(int x, int y)
{
	float new_x, new_y;
	convert_xy(x, y, new_x, new_y);

	for (int i = 0; i < vNum / 3; i++)
	{
		if(motion && vPos[i*3] == move_x && vPos[i * 3 + 1] == move_y)
		{
			vPos[i * 3] = new_x;
			vPos[i * 3 + 1] = new_y;
			move_x = vPos[i * 3];
			move_y = vPos[i * 3 + 1];
		}
	}
}
