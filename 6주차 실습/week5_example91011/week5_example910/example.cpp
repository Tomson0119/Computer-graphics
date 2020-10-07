#include "example.h"

Shader Example::shader = Shader();
std::vector<Triangle> Example::tris = std::vector<Triangle>();

bool Example::animation = false;
int Example::mode = -1;

Example::Example()
{
	tris.push_back(Triangle(0.0f, 0.0f, 0.3f, -0.5f, 0.3f, 0.5f, "right"));
	tris.push_back(Triangle(0.0f, 0.0f, 0.3f, 0.5f, -0.3f, 0.5f, "up"));
	tris.push_back(Triangle(0.0f, 0.0f, -0.3f, 0.5f, -0.3f, -0.5f,"left"));
	tris.push_back(Triangle(0.0f, 0.0f, -0.3f, -0.5f, 0.3f, -0.5f,"down"));
}

void Example::init_shader()
{
	shader.make_shader("vertex.glsl", "fragment.glsl");
	shader.init_buffer(NULL, NULL, 0);
}

GLvoid Example::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < tris.size(); i++)
	{
		shader.reset_buffer(tris.at(i).getPos(), tris.at(i).getColor(), 9);
		shader.use_program();
		tris.at(i).draw();
	}

	glutSwapBuffers();
}

GLvoid Example::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case 't':
		
		if (animation && mode == 0)
			animation = false;
		else
			animation = true;
		mode = 0;
		glutTimerFunc(100, setTimer, 1);
		break;
	case 's':		
		animation = true;
		mode = 1;
		glutTimerFunc(100, setTimer, 1);
		break;
	}
}

GLvoid Example::mouse_event(int button, int state, int x, int y)
{
}

GLvoid Example::setTimer(int value)
{
	for (unsigned int i = 0; i < tris.size(); i++)
	{
		if (mode == 0)
			tris.at(i).move();
		else
			tris.at(i).scale();
	}

	glutPostRedisplay();

	if(animation)
		glutTimerFunc(100, setTimer, 1);
}
