#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

class Util
{
private:
	int window_width;
	int window_height;

	const char* title = "Program";

public:
	Util(int width, int height);

	GLvoid create_window(int argc, char** argv);
	GLvoid init_glew();

	int getWindowWidth() { return window_width; }
	int getWinodwHeight() { return window_height; }
};
