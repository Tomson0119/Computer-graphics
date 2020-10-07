#pragma once

#include "circle.h"

class CircleExample
{
private:

public:
	static Shader shader;
	static std::deque<Circle> circles;
	static GLint mode;
	static float speed;

public:
	CircleExample();

	void init_shader();

	static GLvoid draw();
	static GLvoid reshape(int w, int h);
	static GLvoid key_event(unsigned char key, int x, int y);
	static GLvoid mouse_event(int button, int state, int x, int y);
	static GLvoid setTimer(int value);
};
