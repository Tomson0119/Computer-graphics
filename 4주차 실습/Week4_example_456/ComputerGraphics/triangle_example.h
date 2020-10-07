#pragma once

#include "triangles.h"

class TriangleExample
{
private:
	static Shader shader;

	static std::deque<Triangles> vertexes;

	static GLint mode;

	static float speed;
	static bool stop_animation;

public:
	TriangleExample();

	void init_shader();

	static GLvoid draw();
	static GLvoid reshape(int w, int h);
	static GLvoid key_event(unsigned char key, int x, int y);
	static GLvoid mouse_event(int button, int state, int x, int y);
	static GLvoid setTimer(int value);
};