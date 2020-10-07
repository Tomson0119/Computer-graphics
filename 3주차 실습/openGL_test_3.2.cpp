#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

struct color
{
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

struct box
{
	float pos_x;
	float pos_y;
	float dx;
	float dy;

	color c = color(1.0f, 1.0f, 1.0f);

	box()
	{
		pos_x = 100.0f;
		pos_y = 100.0f;
		dx = 0.05f;
		dy = 0.05f;
	}

	bool empty()
	{
		if (pos_x == 100.0f || pos_y == 100.0f)
			return true;
		else
			return false;
	}
};

GLvoid draw();
GLvoid reshape(int w, int h);
GLvoid key_event(unsigned char key, int x, int y);
GLvoid set_timer(int value);
GLvoid mouse_event(int key, int state, int x, int y);

void getRandomColor(color &c);
void convertPosition(int x, int y);

color outside = color(0.2f, 0.2f, 0.2f);
color inside = color(0.0f, 0.0f, 0.0f);

bool animation = false;

int time = 0;
int index = 0;

float box_size = 0.1f;

box b[10];

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW initialized" << std::endl;

	for (int i = 0; i < 10; i++)
		b[i] = box();

	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse_event);
	glutKeyboardFunc(key_event);

	glutMainLoop();
	return 0;
}

GLvoid draw()
{
	glClearColor(outside.rf, outside.gf, outside.bf, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing part
	for (int i = 0; i < 10; i++)
	{
		if (!b[i].empty())
		{
			glColor3f(b[i].c.rf, b[i].c.gf, b[i].c.bf);
			glRectf(b[i].pos_x - box_size, b[i].pos_y - box_size,
				b[i].pos_x + box_size, b[i].pos_y + box_size);
		}
		
	}

	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		animation = true;
		glutTimerFunc(100, set_timer, 1);
		break;
	case 's':
		animation = false;
		break;
	case 'u':
		box_size += 0.05f;
		break;
	case 'd':
		box_size -= 0.05f;
		break;
	case 'q':
		exit(1);
		break;
	}
	glutPostRedisplay();
}

GLvoid set_timer(int value)
{
	for (int i = 0; i < 10; i++)
	{
		if (!b[i].empty()) {
			b[i].pos_x += b[i].dx;
			b[i].pos_y += b[i].dy;

			if (b[i].pos_x > 1.0f - box_size || b[i].pos_x < -1.0f + box_size)
				b[i].dx *= -1;
			if (b[i].pos_y > 1.0f - box_size || b[i].pos_y < -1.0f + box_size)
				b[i].dy *= -1;
		}
	}	

	glutPostRedisplay();

	if (animation)
		glutTimerFunc(100, set_timer, 1);
}

GLvoid mouse_event(int key, int state, int x, int y)
{
	if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (index < 10) {
			convertPosition(x, y);
			// std::cout << "pos_x : " << pos_x << "\tpos_y : " << pos_y << std::endl;
			getRandomColor(b[index].c);
			glColor3f(b[index].c.rf, b[index].c.gf, b[index].c.bf);
			glRectf(b[index].pos_x - box_size, b[index].pos_y - box_size,
				b[index].pos_x + box_size, b[index].pos_y + box_size);

			index++;
		}
	}
	glutPostRedisplay();
}

void convertPosition(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	width = width / 2;
	height = height / 2;

	b[index].pos_x = (float)(x - width) / (float)width;
	b[index].pos_y = (float)(height - y) / (float)height;
}

void getRandomColor(color &c)
{
	float rf = (float)rand() / (float)RAND_MAX;
	float bf = (float)rand() / (float)RAND_MAX;
	float gf = (float)rand() / (float)RAND_MAX;

	c.set(rf, gf, bf);
}