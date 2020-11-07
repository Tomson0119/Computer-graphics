#include "window.h"
#include "program.h"

#include <gl/freeglut.h>
#include <gl/glew.h>


// Basig elements
Window window = Window(900, 1000);
Program game = Program(window.getWindowWidth(), window.getWinodwHeight());

//Callback functions
GLvoid draw();
GLvoid reshape(int w, int h);
GLvoid key_event(unsigned char key, int x, int y);
GLvoid mouse_event(int button, int state, int x, int y);
GLvoid mouse_motion(int x, int y);
GLvoid setTimer(int value);

int main(int argc, char** argv)
{
	// Initialization
	window.create_window(argc, argv);
	window.init_glew();

	// Initialize program
	game.init();

	// Callbacks
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_event);
	glutTimerFunc(16, setTimer, 1);
	glutMouseFunc(mouse_event);
	glutMotionFunc(mouse_motion);

	glutMainLoop();
	return 0;
}


GLvoid draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);

	game.draw();

	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, window.getWindowWidth(), window.getWinodwHeight());
}

GLvoid key_event(unsigned char key, int x, int y)
{
	game.key_event(key, x, y);
	glutPostRedisplay();
}

GLvoid mouse_event(int button, int state, int x, int y)
{
	game.mouse_event(button, state, x, y);
	glutPostRedisplay();
}

GLvoid mouse_motion(int x, int y)
{
	game.motion_event(x, y);
	glutPostRedisplay();
}

GLvoid setTimer(int value)
{
	game.setTimer();
	glutPostRedisplay();
	glutTimerFunc(16, setTimer, 1);	
}