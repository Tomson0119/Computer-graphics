#include "util.h"
#include "example.h"

#include <gl/freeglut.h>
#include <gl/glew.h>


// Basig elements
Util util = Util(1200, 900);
Example example = Example(util.getWindowWidth(), util.getWinodwHeight());


//Callback functions
GLvoid draw();
GLvoid reshape(int w, int h);
GLvoid key_event(unsigned char key, int x, int y);
GLvoid setTimer(int value);


int main(int argc, char** argv)
{
	// Initialization
	util.create_window(argc, argv);
	util.init_glew();

	// Initialize program
	example.init();

	// Callbacks
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_event);
	glutTimerFunc(16, setTimer, 1);

	glutMainLoop();
	return 0;
}


GLvoid draw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	example.draw();

	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, util.getWindowWidth(), util.getWinodwHeight());
}

GLvoid key_event(unsigned char key, int x, int y)
{
	example.key_event(key, x, y);
	glutPostRedisplay();
}

GLvoid setTimer(int value)
{
	example.setTimer();
	glutPostRedisplay();
	glutTimerFunc(16, setTimer, 1);	
}