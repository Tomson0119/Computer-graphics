#include "example.h"
#include "cube.h"
#include "pyramid.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Example::Example()
	:angle_x(30.0f), angle_y(-30.0f),
	 cube_y(0.0f), pyramid_y(0.0f),
	 rotate_x(0.0f), rotate_y(0.0f),
	 move_x(0.0f), move_y(0.0f), 
	 polygon_mode(GL_FILL), rotate_mode(WHOLE), example_scene(1)
{
	shader = new Shader();

	// Insert objects
	objs.emplace_back(new Line("y"));
	objs.emplace_back(new Line("x"));	
	objs.emplace_back(new Line("z"));
	objs.emplace_back(new Cube());	
	objs.emplace_back(new Pyramid());
	
	// Initialize curObj
	curObj = objs.at(objs.size() - 2);

	camera = Camera();
	viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setViewMat(viewMat);
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

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

void Example::sceneOne_draw()
{
	{ // Lines
		for (unsigned int i = 0; i < 2; i++) {
			objs.at(i)->setWorldMat(glm::mat4(1.0f));
			objs.at(i)->draw(shader);
		}
	}
	{ // Object
		curObj->setWorldMat(glm::mat4(1.0f));
		curObj->setMatRotate(angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
		curObj->setMatRotate(angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
		curObj->draw(shader);
	}
}

void Example::sceneTwo_draw()
{
	{ // Lines
		objs.at(0)->setWorldMat(glm::mat4(1.0f));
		objs.at(0)->draw(shader);
	}
	{ // Object
		for (unsigned int i = 1; i < objs.size(); i++)
		{
			objs.at(i)->setWorldMat(glm::mat4(1.0f));

			objs.at(i)->setMatRotate(angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
			objs.at(i)->setMatRotate(angle_y, glm::vec3(0.0f, 1.0f, 0.0f));

			if (i < 3) objs.at(i)->setMatTranslate(glm::vec3(0.0f, 0.0f, -0.5f));

			if (i == objs.size() - 2)
			{
				objs.at(i)->setMatTranslate(glm::vec3(0.5f, 0.0f, 0.0f));
				objs.at(i)->setMatRotate(cube_y, glm::vec3(0.0f, 1.0f, 0.0f));				
			}
			if (i == objs.size() - 1)
			{
				objs.at(i)->setMatTranslate(glm::vec3(-0.5f, 0.0f, 0.0f));
				objs.at(i)->setMatRotate(pyramid_y, glm::vec3(0.0f, 1.0f, 0.0f));				
			}

			objs.at(i)->draw(shader);
		}

	}
}

void Example::draw()
{
	shader->use_program();
	
	if (example_scene == 1)
		sceneOne_draw();
	else
		sceneTwo_draw();	
}

void Example::key_event(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}

	if (example_scene == 1)
		sceneOne_key_event(key, x, y);
	else
		sceneTwo_key_event(key, x, y);
}

void Example::sceneOne_key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
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
		curObj = objs.at(objs.size() - 2);
		break;
	case 'p':
		curObj = objs.at(objs.size() - 1);
		break;
	case 50:
		example_scene = 2;

		angle_x = 30.0f;
		angle_y = -15.0f;
		cube_y = 0.0f;
		pyramid_y = 0.0f;
		rotate_x = 0.0f;
		rotate_y = 0.0f;

		break;
	}
}

void Example::sceneTwo_key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': case 'X': 
	case 'y': case 'Y':
	case 'b': case 'B':
		if (rotate_y <= 0.0f)
			rotate_y = rotate_speed;
		else
			rotate_y = -rotate_speed;

		if (key == 'x' || key == 'X')
			rotate_mode = CUBE;
		else if (key == 'y' || key == 'Y')
			rotate_mode = PYRAMID;
		else
			rotate_mode = WHOLE;

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
		angle_y = -15.0f;
		cube_y = 0.0f;
		pyramid_y = 0.0f;
		rotate_y = 0.0f;
		break;
	case 49:
		example_scene = 1;

		angle_x = 30.0f;
		angle_y = -30.0f;
		rotate_y = 0.0f;
		
		rotate_mode = WHOLE;
		break;
	}
}

void Example::special_key(int key, int x, int y)
{
	if (example_scene == 1)
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
}

void Example::mouse_event(int button, int state, int x, int y)
{

}

bool Example::setTimer()
{
	if (rotate_mode == WHOLE) {
		angle_x += rotate_x;
		angle_y += rotate_y;
	}
	else if (rotate_mode == CUBE)
		cube_y += rotate_y;
	else
		pyramid_y += rotate_y;
	
	return true;
}
