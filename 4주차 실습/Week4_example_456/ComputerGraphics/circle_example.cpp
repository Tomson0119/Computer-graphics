#include "circle_example.h"

#include "triangle_example.h"

Shader CircleExample::shader = Shader();
std::deque<Circle> CircleExample::circles = std::deque<Circle>();
GLint CircleExample::mode = GL_LINE_LOOP;
float CircleExample::speed = 0.1f;

CircleExample::CircleExample()
{
	
}

void CircleExample::init_shader()
{
	shader.make_shader("vertex.glsl", "fragment.glsl");
	shader.init_buffer(NULL, NULL, 0);
	
}

GLvoid CircleExample::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (Circle obj : circles)
	{
		shader.reset_buffer(obj.getPos(), obj.getColor(), obj.getNum());
		shader.use_program();
		obj.draw();
	}
	glutSwapBuffers();
}

GLvoid CircleExample::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid CircleExample::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case 'q':
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case '1':
		mode = GL_POINTS;
		break;
	case '2':
		mode = GL_LINE_LOOP;
		break;
	}

	glutPostRedisplay();
}

GLvoid CircleExample::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if(circles.size() < 10)
				circles.push_back(Circle(x, y, mode));
			break;
		}
	}
	glutPostRedisplay();
}

GLvoid CircleExample::setTimer(int value)
{
	for (unsigned int i=0;i<circles.size();i++)
	{
		circles.at(i).setRadius(circles.at(i).getRadius() + 0.01f);

		if (circles.at(i).getRadius() > 1.0f)
		{
			int choice = rand() % 2;

			if (choice == 0) {
				if (circles.size() == 1)
					circles.clear();
				else
					circles.erase(circles.begin() + i);
			}
			else {
				circles.at(i).setRadius(0.1f);
			}
		}
		if (circles.size() > 0)
			circles.at(i).setPos();		
	} 
	
	glutPostRedisplay();

	glutTimerFunc(100, setTimer, 1);
}