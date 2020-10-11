#include "second_example.h"

Shader Second_example::shader = Shader();
std::vector<Triangle> Second_example::objs = std::vector<Triangle>();
//Rect Second_example::rect = Rect(0.5f,0.5f);

Second_example::Second_example()
{
	
}

void Second_example::init_shader()
{
	shader.make_shader("vertex.glsl", "fragment.glsl");
	shader.init_buffer(NULL, NULL, 0);

	objs.push_back(Triangle(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, ""));
	objs.push_back(Triangle(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, ""));
	objs.push_back(Triangle(-0.3f, 0.7f, -0.3f, 0.7f, -0.8f, 0.2f, "blue"));

	objs.push_back(Triangle(0.5f, 0.8f, 0.2f, 0.3f, 0.8f, 0.3f, "yellow"));
	objs.push_back(Triangle(0.5f, 0.8f, 0.8f, 0.3f, 0.5f, 0.8f, "yellow"));

	objs.push_back(Triangle(-0.5f, -0.1f, -0.8f, -0.1f, -0.8f, -0.8f, "green"));
	objs.push_back(Triangle(-0.5f, -0.1f, -0.8f, -0.8f, -0.2f, -0.8f, "green"));
	objs.push_back(Triangle(-0.5f, -0.1f, -0.2f, -0.8f, -0.2f, -0.1f, "green"));

	objs.push_back(Triangle(0.5f, -0.1f, 0.2f, -0.4f, 0.3f, -0.8f, "red"));
	objs.push_back(Triangle(0.5f, -0.1f, 0.3f, -0.8f, 0.7f, -0.8f, "red"));
	objs.push_back(Triangle(0.5f, -0.1f, 0.7f, -0.8f, 0.8f, -0.4f, "red"));
}

GLvoid Second_example::draw()
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

GLvoid Second_example::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Second_example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	}
}

GLvoid Second_example::mouse_event(int button, int state, int x, int y)
{
}

GLvoid Second_example::setTimer(int value)
{
	// line to triangle
	objs.at(2).line_to_triangle(-0.4f);


	// triangle to rectangle
	objs.at(3).tri_to_rect(0.2f, 0.8f, 0);
	objs.at(4).tri_to_rect(0.2f, 0.8f, 1);


	// rectangle to pentagon
	objs.at(5).rect_to_pent(-0.7f, -0.4f, 1);
	objs.at(6).rect_to_pent(-0.7f, -0.4f, 2);
	objs.at(7).rect_to_pent(-0.7f, -0.4f, 3);

	objs.at(8).pent_to_point(0.5f, -0.5f);
	objs.at(9).pent_to_point(0.5f, -0.5f);
	objs.at(10).pent_to_point(0.5f, -0.5f);

	glutPostRedisplay();

	glutTimerFunc(100, setTimer, 1);
}
