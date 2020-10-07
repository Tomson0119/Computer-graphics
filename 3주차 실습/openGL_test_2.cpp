#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLvoid draw();
GLvoid reshape(int w, int h);

struct color {
	float rf = 0.0f;
	float gf = 0.0f;
	float bf = 0.0f;

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

void getRandomColors(color &c);
void mouse_event(int button, int state, int x, int y);
void convertPosition(int x, int y);

color outside_color = color(0.0f,0.0f,0.0f);
color inside_color = color(1.0f, 1.0f, 1.0f);

float pos_x, pos_y;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse_event);

	glutMainLoop();
	return 0;
}

GLvoid draw()
{
	glClearColor(outside_color.rf, outside_color.gf, outside_color.bf, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Drawing part
	glColor3f(inside_color.rf, inside_color.gf, inside_color.bf);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);


	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void mouse_event(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertPosition(x, y);
		std::cout << "pos_x : " << pos_x << " pos_y : " << pos_y << std::endl;

		if (pos_x >= -0.5f && pos_x <= 0.5f && pos_y >= -0.5f && pos_y <= 0.5f)
			getRandomColors(inside_color);
		else
			getRandomColors(outside_color);

		glutPostRedisplay();
	}
}

void getRandomColors(color& c)
{
	float rf = (float)rand() / (float)RAND_MAX;
	float gf = (float)rand() / (float)RAND_MAX;
	float bf = (float)rand() / (float)RAND_MAX;

	c.set(rf, gf, bf);
}

void convertPosition(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	width = width / 2;
	height = height / 2;

	pos_x = (float)(x - width) / (float)width;
	pos_y = (float)(y - height) / (float)height;
}