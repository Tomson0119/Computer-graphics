#include "triangle_example.h"

Shader TriangleExample::shader = Shader();
std::deque<Triangles> TriangleExample::vertexes = std::deque<Triangles>();
GLint TriangleExample::mode = GL_TRIANGLES;
float TriangleExample::speed = 0.1f;
bool TriangleExample::stop_animation = true;

TriangleExample::TriangleExample()
{

}

void TriangleExample::init_shader()
{
	shader.make_shader("vertex.glsl", "fragment.glsl");
	shader.init_buffer(NULL, NULL, 3);
}

GLvoid TriangleExample::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shader.use_program();

	for (unsigned int i = 0; i < vertexes.size(); i++)
	{
		shader.reset_buffer(vertexes[i].getPos(), vertexes[i].getColor(), 3);
		shader.use_program();
		vertexes[i].draw(0, 3);
	}

	glutSwapBuffers();
}

GLvoid TriangleExample::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TriangleExample::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case 'f':
		if (vertexes.size() > 0)
		{
			if (mode == GL_TRIANGLES)
			{
				mode = GL_LINE_LOOP;
				for (unsigned int i = 0; i < vertexes.size(); i++)
				{
					vertexes[i].change_mode(mode);
				}
			}
			else if (mode == GL_LINE_LOOP)
			{
				mode = GL_TRIANGLES;
				for (unsigned int i = 0; i < vertexes.size(); i++)
				{
					vertexes[i].change_mode(mode);
				}
			}
		}
		break;
	case 'm':
		stop_animation = false;
		glutTimerFunc(100, setTimer, 1);
		break;
	case 's':
		stop_animation = true;
		break;
	case 'c':
		for (unsigned int i = 0; i < vertexes.size(); i++)
		{
			vertexes[i].change_color();
		}
		break;
	case 'q':
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	}

	glutPostRedisplay();
}

GLvoid TriangleExample::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			std::cout << "x : " << x << " y : " << y << std::endl;

			if (vertexes.size() >= 4)
				vertexes.pop_front();
			vertexes.push_back(Triangles(x, y));
			break;
		}
	}
	glutPostRedisplay();
}

GLvoid TriangleExample::setTimer(int value)
{
	for (unsigned int i = 0; i < vertexes.size(); i++)
	{
		vertexes[i].boundary_check(speed);
		vertexes[i].change_pos();
	}
	glutPostRedisplay();

	if (!stop_animation)
		glutTimerFunc(100, setTimer, 1);
}