#include "window.h"
#include "example.h"

#include <gl/freeglut.h>
#include <gl/glew.h>


// Basig elements
Window window = Window(1200, 900);
Example example = Example(window.getWindowWidth(), window.getWinodwHeight());


// Callback functions
GLvoid draw();
GLvoid reshape(int w, int h);
GLvoid keyDown(unsigned char key, int x, int y);
GLvoid keyUp(unsigned char key, int x, int y);
GLvoid setTimer(int value);


int main(int argc, char** argv)
{
	// Initialization
	window.create_window(argc, argv);
	window.init_glew();

	// Initialize program
	example.init();

	/////////////// Print ////////////////////////
	//////////////////////////////////////////////
	std::cout << "==================== Key ===================" << std::endl;
	std::cout << "//  W : 위로 이동                         //" << std::endl;
	std::cout << "//  A : 왼쪽으로 이동                     //" << std::endl;
	std::cout << "//  S : 아래로 이동                       //" << std::endl;
	std::cout << "//  D : 오른쪽으로 이동                   //" << std::endl;
	std::cout << "//  W : 위로 이동                         //" << std::endl;
	std::cout << "//  M : 와이어모드 켜기/끄기              //" << std::endl;
	std::cout << "//  C : 화면 중심 카메라 회전(시계방향)   //" << std::endl;
	std::cout << "//  V : 화면 중심 카메라 회전(반시계방향) //" << std::endl;
	std::cout << "//  Y : 카메라 중심 회전(반시계방향)      //" << std::endl;
	std::cout << "//  G : 전체 초기화                       //" << std::endl;
	std::cout << "//  1 / 3 : 1인칭 시점 / 3인칭 시점 변경  //" << std::endl;
	std::cout << "============================================" << std::endl;
	//////////////////////////////////////////////

	// Callbacks
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
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
	glViewport(0, 0, window.getWindowWidth(), window.getWinodwHeight());
}

GLvoid keyDown(unsigned char key, int x, int y)
{
	example.keyDown(key, x, y);
	glutPostRedisplay();
}

GLvoid keyUp(unsigned char key, int x, int y)
{
	example.keyUp(key, x, y);
	glutPostRedisplay();
}

GLvoid setTimer(int value)
{
	example.setTimer();
	glutPostRedisplay();
	glutTimerFunc(16, setTimer, 1);	
}
