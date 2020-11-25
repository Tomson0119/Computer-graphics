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
	std::cout << "//  W : ���� �̵�                         //" << std::endl;
	std::cout << "//  A : �������� �̵�                     //" << std::endl;
	std::cout << "//  S : �Ʒ��� �̵�                       //" << std::endl;
	std::cout << "//  D : ���������� �̵�                   //" << std::endl;
	std::cout << "//  W : ���� �̵�                         //" << std::endl;
	std::cout << "//  M : ���̾��� �ѱ�/����              //" << std::endl;
	std::cout << "//  C : ȭ�� �߽� ī�޶� ȸ��(�ð����)   //" << std::endl;
	std::cout << "//  V : ȭ�� �߽� ī�޶� ȸ��(�ݽð����) //" << std::endl;
	std::cout << "//  Y : ī�޶� �߽� ȸ��(�ݽð����)      //" << std::endl;
	std::cout << "//  G : ��ü �ʱ�ȭ                       //" << std::endl;
	std::cout << "//  1 / 3 : 1��Ī ���� / 3��Ī ���� ����  //" << std::endl;
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
