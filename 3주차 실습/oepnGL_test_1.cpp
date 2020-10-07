#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <iostream>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid handleKeyEvent(unsigned char key, int x, int y);
GLvoid setTimer(int value);

struct color {
	float rf;
	float gf;
	float bf;

	color(float rf, float gf, float bf)
	{
		set(rf, gf, bf);
	}
	
	void set(float rf, float gf, float bf)
	{
		this->rf = rf;
		this->gf = gf;
		this->bf = bf;
	}
};

color c = color(1.0f, 1.0f, 1.0f);
int time = 0;
bool stop_animation = false;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Init Initialized\n";


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(handleKeyEvent);
	//glutTimerFunc(100, setTimer, 1);
	
	
	
	glutMainLoop();	
	return 0;
}

GLvoid drawScene()
{
	glClearColor(c.rf, c.gf, c.bf, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// -- drawing part





	glutSwapBuffers();
}

GLvoid handleKeyEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		c.set(1.0f, 0.0f, 0.0f);
		break;
	case 'g':
		c.set(0.0f, 1.0f, 0.0f);
		break;
	case 'b':
		c.set(0.0f, 0.0f, 1.0f);
		break;
	case 'w':
		c.set(1.0f, 1.0f, 1.0f);
		break;
	case 'k':
		c.set(0.0f, 0.0f, 0.0f);
		break;
	case 't':
		stop_animation = false;
		glutTimerFunc(100, setTimer, 1);
		break;
	case 's':
		stop_animation = true;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid setTimer(int value)
{
	time = (time + 1) % 20;
	if (time == 0) {
		c.set(float(rand()) / float(RAND_MAX),
			float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX));
	}
	glutPostRedisplay();

	if(!stop_animation)
		glutTimerFunc(100, setTimer, 1);
}