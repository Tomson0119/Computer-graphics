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
	move_x(0.0f), move_z(0.8f), way(0.0f), amount(0.01f),
	move_y(0.0f), jump(0.0f), door(0.0f), door_move(0.0f),
	animation(0.0f), increase(0.0f), turning(0.0f)
{
	shader = new Shader();

	globalMat = glm::mat4(1.0f);
	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);

	// Stage 0 ~ 5
	{
		objs.push_back(new Rect("red"));
		objs.push_back(new Rect("yellow"));
		objs.push_back(new Rect("purple"));
		objs.push_back(new Rect("gray"));
		objs.push_back(new Rect("blue"));
		objs.push_back(new Rect("sky"));
	}
	// Robot 6 ~ 12
	{
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("yellow"));
		objs.push_back(new Cube("green"));
		objs.push_back(new Cube("green"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));

		// Face
		objs.push_back(new Cube("brown"));
	}
	// Tree 13 ~ 14
	{ 
		objs.push_back(new Cube("brown"));
		objs.push_back(new Sphere("green"));
	}
	// Running 15 ~ 25
	{ 
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));
		objs.push_back(new Sphere("yellow"));

		// Person
		objs.push_back(new Sphere("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
	}
	// Bar 26 ~ 34
	{
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));

		// Person
		objs.push_back(new Sphere("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
	}
	
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
	// Stage
	{ 
		objs.at(0)->setWorldTranslate(glm::vec3(0.0f, 0.0f, 1.0f));
		objs.at(0)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));

		objs.at(1)->setWorldTranslate(glm::vec3(1.0f, 0.0f, 0.0f));
		objs.at(1)->setWorldRotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		objs.at(1)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));

		objs.at(2)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));
		objs.at(2)->setWorldRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		objs.at(2)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));

		objs.at(3)->setWorldTranslate(glm::vec3(0.0f, 0.0f, -1.0f));
		objs.at(3)->setWorldScale(glm::vec3(5.0f, 2.5f, 1.0f));

		objs.at(4)->setWorldTranslate(glm::vec3(0.0f, 0.5f, 0.0f));
		objs.at(4)->setWorldRotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		objs.at(4)->setWorldScale(glm::vec3(5.0f, 5.0f, 1.0f));

		objs.at(5)->setWorldTranslate(glm::vec3(0.0f, -0.5f, 0.0f));
		objs.at(5)->setWorldRotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		objs.at(5)->setWorldScale(glm::vec3(5.0f, 5.0f, 1.0f));
	}
		 
	// Robot
	{ 
		objs.at(6)->setWorldScale(glm::vec3(0.2f, 0.2f, 0.2f));
		objs.at(6)->setWorldTranslate(glm::vec3(0.0f, -1.9f, 0.0f));
		
		objs.at(7)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.1f));
		objs.at(7)->setWorldTranslate(glm::vec3(0.0f, -3.1f, 0.0f));

		objs.at(8)->setWorldScale(glm::vec3(0.06f, 0.2f, 0.06f));
		objs.at(8)->setWorldTranslate(glm::vec3(-0.2f, -0.2f, 0.0f));

		objs.at(9)->setWorldScale(glm::vec3(0.06f, 0.2f, 0.06f));
		objs.at(9)->setWorldTranslate(glm::vec3(0.2f, -0.2f, 0.0f));

		objs.at(10)->setWorldScale(glm::vec3(0.05f, 0.2f, 0.1f));
		objs.at(10)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));

		objs.at(11)->setWorldScale(glm::vec3(0.05f, 0.2f, 0.1f));
		objs.at(11)->setWorldTranslate(glm::vec3(1.0f, 0.0f, 0.0f));

		objs.at(12)->setWorldScale(glm::vec3(0.08f, 0.08f, 0.08f));
		objs.at(12)->setWorldTranslate(glm::vec3(0.0f, -3.9f, 0.08f));
	}

	// Tree
	{ 
		objs.at(13)->setWorldTranslate(glm::vec3(0.7f, -0.3f, 0.7f));
		objs.at(13)->setWorldScale(glm::vec3(0.4f, 1.0f, 0.4f));
		
		objs.at(14)->setWorldTranslate(glm::vec3(0.7f, 0.0f, 0.7f));
		objs.at(14)->setWorldScale(glm::vec3(0.4f, 0.4f, 0.4f));
	}
	
	// Running
	{ 
		objs.at(15)->setWorldTranslate(glm::vec3(-0.7f, -0.48f, 0.7f));
		objs.at(15)->setWorldScale(glm::vec3(0.8f, 0.1f, 0.5f));

		objs.at(16)->setWorldTranslate(glm::vec3(-0.84f, -0.45f, 0.78f));
		objs.at(16)->setWorldScale(glm::vec3(0.1f, 0.3f, 0.1f));

		objs.at(17)->setWorldTranslate(glm::vec3(-0.84f, -0.45f, 0.62f));
		objs.at(17)->setWorldScale(glm::vec3(0.1f, 0.3f, 0.1f));

		objs.at(18)->setWorldTranslate(glm::vec3(-0.84f, -0.38f, 0.7f));
		objs.at(18)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.5f));

		objs.at(19)->setWorldTranslate(glm::vec3(-0.7f, -0.48f, 0.7f));
		objs.at(19)->setWorldScale(glm::vec3(0.4f, 0.1f, 0.2f));

		// Person
		objs.at(20)->setWorldTranslate(glm::vec3(-0.7f, -0.3f, 0.7f));
		objs.at(20)->setWorldScale(glm::vec3(0.05f, 0.05f, 0.05f));

		objs.at(21)->setWorldTranslate(glm::vec3(-0.7f, -0.36f, 0.7f));
		objs.at(21)->setWorldScale(glm::vec3(0.15f, 0.2f, 0.15f));

		objs.at(22)->setWorldTranslate(glm::vec3(0.0f, 0.0f, 0.74f));
		objs.at(22)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(23)->setWorldTranslate(glm::vec3(0.0f, 0.0f, 0.66f));
		objs.at(23)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(24)->setWorldTranslate(glm::vec3(0.0f, -0.05f, 0.72f));
		objs.at(24)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(25)->setWorldTranslate(glm::vec3(0.0f, -0.05f, 0.68f));
		objs.at(25)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));
	}
	
	// Bar
	{ 
		objs.at(26)->setWorldTranslate(glm::vec3(0.6f, -0.3f, -0.8f));
		objs.at(26)->setWorldScale(glm::vec3(0.1f, 1.0f, 0.1f));

		objs.at(27)->setWorldTranslate(glm::vec3(0.6f, -0.3f, -0.5f));
		objs.at(27)->setWorldScale(glm::vec3(0.1f, 1.0f, 0.1f));

		objs.at(28)->setWorldTranslate(glm::vec3(0.6f, -0.1f, -0.65f));
		objs.at(28)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.83f));

		// Person
		objs.at(29)->setWorldTranslate(glm::vec3(0.0f, -0.07f, -0.66f));
		objs.at(29)->setWorldScale(glm::vec3(0.05f, 0.05f, 0.05f));

		objs.at(30)->setWorldTranslate(glm::vec3(0.0f, -0.13f, -0.66f));
		objs.at(30)->setWorldScale(glm::vec3(0.15f, 0.2f, 0.15f));

		objs.at(31)->setWorldTranslate(glm::vec3(0.0f, -0.06f, -0.70f));
		objs.at(31)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(32)->setWorldTranslate(glm::vec3(0.0f, -0.06f, -0.62f));
		objs.at(32)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(33)->setWorldTranslate(glm::vec3(0.0f, -0.2f, -0.68f));
		objs.at(33)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));

		objs.at(34)->setWorldTranslate(glm::vec3(0.0f, -0.2f, -0.64f));
		objs.at(34)->setWorldScale(glm::vec3(0.1f, 0.2f, 0.05f));
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

	// Stages
	{ 
		objs.at(0)->setWorldTranslate(glm::vec3(0.0f, door, 0.0f));
		for (unsigned int i = 1; i < 6; i++)
			objs.at(i)->draw(shader);		
	}

	// Robot
	{ 
		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(move_x, move_y, move_z));
		globalMat = glm::rotate(globalMat, glm::radians(way), glm::vec3(0.0f, 1.0f, 0.0f));		
		shader->setOutWorldTransform(globalMat);
		objs.at(6)->draw(shader);
		objs.at(7)->draw(shader);
		objs.at(12)->draw(shader);

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

	// Tree
	{ 
		globalMat = glm::mat4(1.0f);
		shader->setOutWorldTransform(globalMat);
		objs.at(13)->draw(shader);
		objs.at(14)->setWorldScale(glm::vec3(1.0f + animation / 10.0f, 1.0f + animation / 10.0f, 1.0f + animation / 10.0f));
		objs.at(14)->draw(shader);	
	}

	// Running
	{ 
		if (animation != 0.0f)
			objs.at(19)->setWorldRotate(-0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		for (unsigned int i = 15; i <= 21; i++)
		{
			objs.at(i)->draw(shader);
		}		

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.7f, -0.36f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(robot), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(22)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.7f, -0.36f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-robot), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(23)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.7f, -0.4f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-robot), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(24)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.7f, -0.4f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(robot), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(25)->draw(shader);
	}

	// Bar
	{
		globalMat = glm::mat4(1.0f);
		shader->setOutWorldTransform(globalMat);
		objs.at(26)->draw(shader);
		objs.at(27)->draw(shader);
		objs.at(28)->draw(shader);
		
		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(0.6f, -0.1f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(turning), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		for (unsigned int i = 29; i <= 34; i++)
			objs.at(i)->draw(shader);
	}
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
		if(move_z >= -0.8f) move_z -= amount;
		break;
	case 'a': case 'A':
		way = -90.f;
		if (move_x >= -0.8f) move_x -= amount;
		break;
	case 's': case 'S':
		way = 0.0f;
		if (move_z <= 0.8f) move_z += amount;
		break;
	case 'd': case 'D':
		way = 90.0f;
		if (move_x <= 0.8f) move_x += amount;
		break;
	case 'j': case 'J':
		jump = 0.02f;
		break;
	case 'p': case 'P':
		if (increase == 0.0f) increase = 0.01f;
		else increase = 0.0f;
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

	animation += increase;
	if (animation > 0.1f || animation < -0.1f) increase *= -1.0f;

	turning += 0.5f;

	return true;
}


