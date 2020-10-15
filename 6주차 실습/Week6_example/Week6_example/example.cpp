#include "example.h"
#include "cube.h"
#include "pyramid.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Example::Example()
	:angle_x(30.0f), angle_y(-30.0f),
	 rotate_x(0.0f), rotate_y(0.0f), polygon_mode(GL_FILL)
{
	shader = new Shader();
	lines.emplace_back(new Line("x"));
	lines.emplace_back(new Line("y"));

	objs.emplace_back(new Pyramid());
	transformMat = glm::mat4(1.0f);
}

Example::~Example()
{
	for (auto p : lines)
		delete p;
	lines.clear();
	lines.shrink_to_fit();

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
	for (unsigned int i = 0; i < lines.size(); i++)
		lines.at(i)->setVertexArray();

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
}

void Example::draw()
{
	shader->use_program();

	transformMat = glm::mat4(1.0f);
	shader->setMatTransform("transform", transformMat);
	for (unsigned int i = 0; i < lines.size(); i++)
		lines.at(i)->draw();

	transformMat = glm::rotate(transformMat, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformMat = glm::rotate(transformMat, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setMatTransform("transform", transformMat);
	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->draw();
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
		
		break;
	case 'p':
		
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
