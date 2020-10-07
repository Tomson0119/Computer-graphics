#include "example.h"

Shader Example::shader = Shader();
std::vector<Triangle> Example::tris = std::vector<Triangle>();
Rect Example::rect = Rect();

Example::Example()
{

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
		shader.reset_buffer(tris.at(i).getPos(), tris.at(i).getColor(), tris.at(i).getDataSize());
		shader.use_program();
		tris.at(i).draw();
	}
	shader.reset_buffer(rect.getPos(), rect.getColor(), rect.getDataSize());
	shader.use_program();
	rect.draw();

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
	}
}

GLvoid Example::mouse_event(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		std::cout << "X : " << x << "  Y : " << y << std::endl;

		if (tris.size() < 10)
			tris.push_back(Triangle(x, y));
	}
	glutPostRedisplay();
}

GLvoid Example::setTimer(int value)
{
	// Flip vertexes of each triangle
	for (unsigned int i = 0; i < tris.size(); i++)
	{
		// flip vertexes of triangle depending on boundary
		tris.at(i).setAnimation(rect);
	}
	glutPostRedisplay();
	glutTimerFunc(100, setTimer, 1);
}
