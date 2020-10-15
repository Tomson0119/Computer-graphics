#include "util.h"
#include "example.h"

#include <ctime>


// Basig elements
Util util = Util(800, 800);
Example example = Example();


//Callback functions
GLvoid draw();
GLvoid reshape(int w, int h);
GLvoid key_event(unsigned char key, int x, int y);
GLvoid mouse_event(int button, int state, int x, int y);
GLvoid setTimer(int value);
GLvoid special_key_down(int key, int x, int y);


int main(int argc, char** argv)
{
	srand((unsigned int)time(0));

	// Initialization
	util.create_window(argc, argv);
	util.init_glew();

	// Initialize program
	example.init();

	// Callbacks
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_event);
	glutSpecialFunc(special_key_down);
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
	glViewport(0, 0, w, h);
}

GLvoid key_event(unsigned char key, int x, int y)
{
	example.key_event(key, x, y);
	glutPostRedisplay();
}

GLvoid mouse_event(int button, int state, int x, int y)
{
	example.mouse_event(button, state, x, y);
}

GLvoid setTimer(int value)
{
	example.setTimer();
	glutPostRedisplay();
	glutTimerFunc(16, setTimer, 1);	
}

GLvoid special_key_down(int key, int x, int y)
{
	example.special_key(key, x, y);
	glutPostRedisplay();
}