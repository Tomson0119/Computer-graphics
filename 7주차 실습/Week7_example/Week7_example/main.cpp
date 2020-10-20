#include "util.h"
#include "example.h"

// Basig elements
Util util = Util(800, 800);
Example example = Example();


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
	example.init(util.getWindowWidth(), util.getWinodwHeight());

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

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