#pragma once

#include "util.h"

class Triangle
{
private:
	float* vPos;
	float* vColor;

	float move_value;
	float scale_value;
	
	float first_x, first_y;
	float move_x, move_y;

	GLint mode;
	bool motion;

	const float speed = 0.01f;
	const int vNum = 9;

	const char* direction;

	void setPos(float x1, float y1, float x2, float y2, float x3, float y3);
	void setColor(const char* direction);

	void convert_xy(int x, int y, float& new_x, float& new_y);
	bool check_line();


public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3, const char* direction);

	void draw();

	float* getPos() { return vPos; }
	float* getColor() { return vColor; }
	int getNum() { return vNum; }

	void move();
	void scale();

	// For second example
	void line_to_triangle(float bound);
	void tri_to_rect(float min_x, float max_x, int toggle);
	void rect_to_pent(float bound_x,float bound_y, int toggle);
	void pent_to_point(float pos_x, float pos_y);

	// For third example
	void change_mode(GLint mode);
	void setMotion(int x, int y);
	void move_vertex_by_mouse(int x, int y);
};