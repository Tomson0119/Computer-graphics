#include "example.h"
#include "cube.h"
#include "pyramid.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Example::Example()
	:angle_x(30.0f), angle_y(-30.0f),
	 rotate_x(0.0f), rotate_y(0.0f), 
	 move_x(0.0f), move_y(0.0f), polygon_mode(GL_FILL)
{
	shader = new Shader();

	objs.emplace_back(new Line("x"));
	objs.emplace_back(new Line("y"));
	objs.emplace_back(new Cube());
	objs.emplace_back(new Pyramid());

	curObj = objs.at(2);

	transformMat = glm::mat4(1.0f);
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	objs.clear();
	objs.shrink_to_fit();

	delete shader;
}

void Example::init()
{	
	init_shader();
	init_vertexArray();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void Example::init_shader()
{
	shader->make_shader("vertex.glsl", "fragment.glsl");
}

void Example::init_vertexArray()
{
	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
}

void Example::draw()
{
	shader->use_program();
	 
	{ // Lines
		transformMat = glm::mat4(1.0f);
		shader->setMatTransform("transform", transformMat);
		for (unsigned int i = 0; i < 2; i++)
			objs.at(i)->draw();
	}
	{ // Object
		transformMat = glm::translate(transformMat, glm::vec3(move_x, move_y, 0.0f));
		transformMat = glm::rotate(transformMat, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
		transformMat = glm::rotate(transformMat, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setMatTransform("transform", transformMat);
		curObj->draw();
	}
}

void Example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case 'h':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		break;
	case 'x': case 'X':
		if (rotate_x <= 0.0f)
			rotate_x = rotate_speed;
		else
			rotate_x = -rotate_speed;
		rotate_y = 0.0f;
		break;
	case 'y': case 'Y':
		if (rotate_y <= 0.0f)
			rotate_y = rotate_speed;
		else
			rotate_y = -rotate_speed;
		rotate_x = 0.0f;
		break;
	case 'w': case 'W':
		if (polygon_mode == GL_LINE)
			polygon_mode = GL_FILL;
		else
			polygon_mode = GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;
	case 's':
		angle_x = 30.0f;
		angle_y = -30.0f;
		rotate_x = 0.0f;
		rotate_y = 0.0f;
		break;
	case 'c':
		curObj = objs.at(2);
		break;
	case 'p':
		curObj = objs.at(3);
		break;
	}

}

void Example::special_key(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		move_x -= move_dist;
		break;
	case GLUT_KEY_RIGHT:
		move_x += move_dist;
		break;
	case GLUT_KEY_UP:
		move_y += move_dist;
		break;
	case GLUT_KEY_DOWN:
		move_y -= move_dist;
		break;
	}
}

void Example::mouse_event(int button, int state, int x, int y)
{

}

bool Example::setTimer()
{
	angle_x += rotate_x;
	angle_y += rotate_y;
	return true;
}
