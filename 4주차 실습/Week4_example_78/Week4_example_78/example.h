#pragma once

#include "shader.h"
#include "triangle.h"
#include "rectangle.h"

class Example
{
private:
	static Shader shader;
	static std::vector<Triangle> tris;
	static Rect rect;

public:
	Example();

	void init_shader();

	static GLvoid draw();
	static GLvoid reshape(int w, int h);
	static GLvoid key_event(unsigned char key, int x, int y);
	static GLvoid mouse_event(int button, int state, int x, int y);
	static GLvoid setTimer(int value);
};