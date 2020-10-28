#include "example.h"
#include "rectangle.h"
#include "cube.h"
#include "sphere.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>


Example::Example()
	: window_w(0), window_h(0), angle(0.0f), camera_turn(0),
	polygon_mode(GL_LINE), robot(0.0f), robot_rotate(1.0f),
	move_x(0.0f), move_z(0.0f), way(0.0f), amount(0.01f),
	move_y(0.0f), jump(0.0f), door(0.0f), door_move(0.0f)
{
	shader = new Shader();

	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);

	// Stage
	objs.push_back(new Rect("red"));
	objs.push_back(new Rect("yellow"));
	objs.push_back(new Rect("blue"));
	objs.push_back(new Rect("green"));
	objs.push_back(new Rect("purple"));
	objs.push_back(new Rect("sky"));

	// Robot
	objs.push_back(new Cube("red"));
	objs.push_back(new Cube("yellow"));
	objs.push_back(new Cube("green"));
	objs.push_back(new Cube("green"));
	objs.push_back(new Cube("red"));
	objs.push_back(new Cube("red"));

	// Tree
	objs.push_back(new Cube("brown"));
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

	delete shader;
}

void Example::init(int window_w, int window_h)
{
	this->window_w = window_w;
	this->window_h = window_h;

	shader->make_shader("vertex.glsl", "fragment.glsl");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	

	// Initialize View Matrix
	viewMat = glm::lookAt(camera.Position, camera.Direction, camera.Up);

	// Initialize Projection Matrix
	projMat = glm::perspective(glm::radians(45.0f),
		(float)window_w / (float)window_h, 0.1f, 50.0f);

	// Initialize Objects
	for (unsigned int i = 0; i < objs.size(); i++)
	{
		if (i == 0)
		{
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.0f, 1.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));
		}
		if (i == 1) 
		{
			objs.at(i)->setWorldTranslate(glm::vec3(1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldRotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));
		}
		if (i == 2)
		{
			objs.at(i)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));
		}
		if (i == 3)
		{
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.0f, -1.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));
		}
		if (i == 4)
		{
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.5f, 0.0f));
			objs.at(i)->setWorldRotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 5.0f, 1.0f));
		}
		if (i == 5)
		{
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -0.5f, 0.0f));
			objs.at(i)->setWorldRotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(5.0f, 5.0f, 1.0f));
		}
		

		if (i == 6)
		{			
			objs.at(i)->setWorldScale(glm::vec3(0.2f, 0.2f, 0.2f));
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -1.9f, 0.0f));
		}
		if (i == 7 || i == objs.size()-1) {			
			if (i == objs.size() - 1) {
				objs.at(i)->setWorldScale(glm::vec3(0.08f, 0.08f, 0.08f));
				objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -3.9f, 0.08f));
			}
			else {
				objs.at(i)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.1f));
				objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -3.1f, 0.0f));
			}
		}
		if (i == 8)
		{
			objs.at(i)->setWorldScale(glm::vec3(0.06f, 0.2f, 0.06f));
			objs.at(i)->setWorldTranslate(glm::vec3(-0.2f, -0.2f, 0.0f));
		}
		if (i == 9)
		{
			objs.at(i)->setWorldScale(glm::vec3(0.06f, 0.2f, 0.06f));
			objs.at(i)->setWorldTranslate(glm::vec3(0.2f, -0.2f, 0.0f));
		}
		if (i == 10)
		{
			objs.at(i)->setWorldScale(glm::vec3(0.05f, 0.2f, 0.1f));
			objs.at(i)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		if (i == 11)
		{
			objs.at(i)->setWorldScale(glm::vec3(0.05f, 0.2f, 0.1f));
			objs.at(i)->setWorldTranslate(glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

void Example::draw()
{
	shader->use_program();

	if (camera_turn == 0) {
		viewMat = glm::lookAt(camera.Position, camera.Direction, camera.Up);
		viewMat = glm::rotate(viewMat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
		viewMat = glm::lookAt(camera.Position, camera.Position + camera.Direction, camera.Up);


	shader->setViewTransform(viewMat);
	shader->setProjTransform(projMat);

	globalMat = glm::mat4(1.0f);
	shader->setOutWorldTransform(globalMat);

	{ // Stages
		objs.at(0)->setWorldTranslate(glm::vec3(0.0f, door, 0.0f));
		for (unsigned int i = 0; i < 6; i++)
			objs.at(i)->draw(shader);		
	}

	{ // Robot
		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));		
		shader->setOutWorldTransform(globalMat);
		objs.at(6)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(7)->draw(shader);
		objs.at(objs.size() - 1)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, -0.43f + move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(robot), glm::vec3(1.0f, 0.0f, 0.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(8)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, -0.43f + move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-robot), glm::vec3(1.0f, 0.0f, 0.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(9)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, -0.38f + move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(robot), glm::vec3(1.0f, 0.0f, 0.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(10)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, -0.38f + move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-robot), glm::vec3(1.0f, 0.0f, 0.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(11)->draw(shader);
	}

	{ // Tree
		//globalMat = glm::globalMat()
	}	
}

void Example::globalTransform(glm::vec3 trans, float angle, glm::vec3 axis)
{
	/*globalMat = glm::mat4(1.0f);
	globalMat = glm::translate(trans);
	globalMat = glm::rotate(globalMat, glm::radians(angle), );*/
}

void Example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: case 'q': case 'Q':
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	case 'o': case 'O':
		door_move = move_dist;
		break;
	case 'z':
		camera.Position += glm::vec3(0.0f, 0.0f, 0.1f);
		break;
	case 'Z':
		camera.Position += glm::vec3(0.0f, 0.0f, -0.1f);
		break;
	case 'y': case 'Y':
		camera_turn = 1;
		camera.Direction = glm::rotate(camera.Direction, glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'r': case 'R':
		camera_turn = 0;
		angle += 1.5f;
		break;
	case 'w': case 'W':
		way = 180.0f;
		break;
	case 'a': case 'A':
		way = -90.f;
		break;
	case 's': case 'S':
		way = 0.0f;
		break;
	case 'd': case 'D':
		way = 90.0f;
		break;
	case 'j': case 'J':
		jump = 0.02f;
		break;
	case 'm': case 'M':
		if (polygon_mode == GL_LINE)
			polygon_mode = GL_FILL;
		else
			polygon_mode = GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;
	}
}

bool Example::setTimer()
{	
	if (door < 1.0f) door += door_move;
	robot += robot_rotate;
	if (robot >= 45.0f || robot <= -45.0f) robot_rotate *= -1.0f;

	if (move_y + jump < 0.0f)
		move_y = 0.0f, jump = 0.0f;
	else {
		move_y += jump;
		if (move_y > 0.2f)
			jump *= -1.0f;
	}
		
	if (way == 90.0f)
	{
		move_x += amount;
		if (move_x > 0.8f) way = -90.0f;
	}
	if (way == -90.0f)
	{
		move_x -= amount;
		if (move_x < -0.8f) way = 90.0f;
	}
	if (way == 180.0f)
	{
		move_z -= amount;
		if (move_z < -0.8f)	way = 0.0f;
	}
	if (way == 0.0f)
	{
		move_z += amount;
		if (move_z > 0.8f) way = 180.0f;
	}
	return true;
}


