#include "third_example.h"

Shader Third_example::shader = Shader();
std::vector<Triangle> Third_example::objs = std::vector<Triangle>();
int Third_example::action = 0;

Third_example::Third_example()
{

}

void Third_example::init_shader()
{
	shader.make_shader("vertex.glsl", "fragment.glsl");
	shader.init_buffer(NULL, NULL, 0);

	objs.push_back(Triangle(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, ""));
	objs.push_back(Triangle(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, ""));

	objs.push_back(Triangle(0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 0.5f, ""));
	objs.push_back(Triangle(0.0f, 0.0f, -0.5f, 0.5f, -0.5f, -0.5f, ""));
	objs.push_back(Triangle(0.0f, 0.0f, -0.5f, -0.5f, 0.5f, -0.5f, ""));
	objs.push_back(Triangle(0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.5f, ""));

	for (unsigned int i = 0; i < objs.size(); i++)
	{
		objs.at(i).change_mode(GL_LINE_LOOP);
	}
}

GLvoid Third_example::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < objs.size(); i++)
	{
		shader.reset_buffer(objs.at(i).getPos(), objs.at(i).getColor(), objs.at(i).getNum());
		shader.use_program();
		objs.at(i).draw();
	}

	glutSwapBuffers();
}

GLvoid Third_example::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Third_example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	}
}

GLvoid Third_example::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			action = 1;
			for (unsigned int i = 2; i < objs.size(); i++)
				objs.at(i).setMotion(x,y);
			break;
		}
	}
	else if (state == GLUT_UP)
	{
		action = 0;
		for (unsigned int i = 2; i < objs.size(); i++)
			objs.at(i).setMotion(-1, -1);
	}
}

GLvoid Third_example::motion(int x, int y)
{
	if (action == 1) {
		for (unsigned int i = 0; i < objs.size(); i++)
		{
			objs.at(i).move_vertex_by_mouse(x, y);
		}
	}

	glutPostRedisplay();
}

GLvoid Third_example::setTimer(int value)
{
	

	glutPostRedisplay();

	glutTimerFunc(100, setTimer, 1);
}
