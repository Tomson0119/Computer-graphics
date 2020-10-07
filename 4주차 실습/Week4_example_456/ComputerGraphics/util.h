#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <deque>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

class Util
{
public:
	Util();

	GLvoid create_window(int argc, char** argv);
	GLvoid init_glew();
};
