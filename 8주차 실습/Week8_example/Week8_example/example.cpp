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
	animation(0.0f), increase(0.01f), turning(0.0f), 
	bench(0.0f), bench_rotate(0.5f), trigger(false),
	bench_bar(0.0f), bench_bar_amount(0.00022f)
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

	// Bench 35 ~ 50
	{
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));
		objs.push_back(new Cube("blue"));

		objs.push_back(new Cube("blue"));
		objs.push_back(new Sphere("red"));
		objs.push_back(new Sphere("red"));
		objs.push_back(new Sphere("yellow"));
		objs.push_back(new Sphere("yellow"));

		// Person
		objs.push_back(new Sphere("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("red"));
		objs.push_back(new Cube("yellow"));
		objs.push_back(new Cube("yellow"));
		objs.push_back(new Cube("green"));
		objs.push_back(new Cube("green"));
	}

	{ // Tower 51 ~ 53
		objs.push_back(new Cube("yellow"));
		objs.push_back(new Cube("purple"));
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

	// Bench
	{
		objs.at(35)->setWorldTranslate(glm::vec3(-0.6f, -0.48f, -0.6f));
		objs.at(35)->setWorldScale(glm::vec3(0.3f, 0.1f, 0.6f));

		objs.at(36)->setWorldTranslate(glm::vec3(-0.68f, -0.44f, -0.7f));
		objs.at(36)->setWorldScale(glm::vec3(0.1f, 0.3f, 0.1f));

		objs.at(37)->setWorldTranslate(glm::vec3(-0.52f, -0.44f, -0.7f));
		objs.at(37)->setWorldScale(glm::vec3(0.1f, 0.3f, 0.1f));

		objs.at(38)->setWorldTranslate(glm::vec3(-0.6f, -0.33f, -0.66f));
		objs.at(38)->setWorldScale(glm::vec3(0.7f, 0.03f, 0.03f));

		objs.at(39)->setWorldTranslate(glm::vec3(-0.7f, -0.33f, -0.66f));
		objs.at(39)->setWorldScale(glm::vec3(0.03f, 0.1f, 0.1f));

		objs.at(40)->setWorldTranslate(glm::vec3(-0.5f, -0.33f, -0.66f));
		objs.at(40)->setWorldScale(glm::vec3(0.03f, 0.1f, 0.1f));

		objs.at(41)->setWorldTranslate(glm::vec3(-0.73f, -0.33f, -0.66f));
		objs.at(41)->setWorldScale(glm::vec3(0.03f, 0.07f, 0.07f));

		objs.at(42)->setWorldTranslate(glm::vec3(-0.47f, -0.33f, -0.66f));
		objs.at(42)->setWorldScale(glm::vec3(0.03f, 0.07f, 0.07f));


		// Person
		objs.at(43)->setWorldTranslate(glm::vec3(-0.6f, -0.44f, -0.7f));
		objs.at(43)->setWorldScale(glm::vec3(0.05f, 0.05f, 0.05f));

		objs.at(44)->setWorldTranslate(glm::vec3(-0.6f, -0.45f, -0.65f));
		objs.at(44)->setWorldScale(glm::vec3(0.15f, 0.2f, 0.15f));

		objs.at(45)->setWorldTranslate(glm::vec3(-0.62f, -0.45f, -0.58f));
		objs.at(45)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.2f));

		objs.at(46)->setWorldTranslate(glm::vec3(-0.58f, -0.45f, -0.58f));
		objs.at(46)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.2f));

		objs.at(47)->setWorldTranslate(glm::vec3(0.0f, 0.02f, -0.66f));
		objs.at(47)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.05f));

		objs.at(48)->setWorldTranslate(glm::vec3(0.0f, 0.02, -0.66f));
		objs.at(48)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.05f));

		objs.at(49)->setWorldTranslate(glm::vec3(0.0f, 0.06f, -0.66f));
		objs.at(49)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.05f));

		objs.at(50)->setWorldTranslate(glm::vec3(0.0f, 0.06f, -0.66f));
		objs.at(50)->setWorldScale(glm::vec3(0.05f, 0.1f, 0.05f));
	}

	// Tower
	{
		objs.at(51)->setWorldTranslate(glm::vec3(0.0f, -0.43f, 0.0f));
		objs.at(51)->setWorldScale(glm::vec3(0.4f, 0.4f, 0.4f));

		objs.at(52)->setWorldTranslate(glm::vec3(0.0f, -0.24f, 0.0f));
		objs.at(52)->setWorldScale(glm::vec3(0.5f, 0.5f, 0.5f));

		objs.at(53)->setWorldTranslate(glm::vec3(0.0f, -0.07f, 0.0f));
		objs.at(53)->setWorldScale(glm::vec3(0.3f, 0.3f, 0.3f));
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
		if (trigger)
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

	// Bench
	{
		globalMat = glm::mat4(1.0f);
		shader->setOutWorldTransform(globalMat);
		for (unsigned int i = 35; i <= 37; i++)
			objs.at(i)->draw(shader);
		for (unsigned int i = 43; i <= 46; i++)
			objs.at(i)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(0.0f,bench_bar, 0.0f));
		shader->setOutWorldTransform(globalMat);
		for (unsigned int i = 38; i <= 42; i++)
			objs.at(i)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.64f, -0.42f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(bench), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(47)->draw(shader);
		
		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.64f, -0.42f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(bench), glm::vec3(0.0f, 0.0f, 1.0f));
		if(trigger)
			objs.at(49)->setWorldRotate(-bench_rotate * 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);		
		objs.at(49)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.56f, -0.42f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-bench), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		objs.at(48)->draw(shader);

		globalMat = glm::mat4(1.0f);
		globalMat = glm::translate(glm::vec3(-0.56f, -0.42f, 0.0f));
		globalMat = glm::rotate(globalMat, glm::radians(-bench), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setOutWorldTransform(globalMat);
		if(trigger)
			objs.at(50)->setWorldRotate(bench_rotate * 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		objs.at(50)->draw(shader);
	}

	// Tower
	{
		globalMat = glm::mat4(1.0f);
		shader->setOutWorldTransform(globalMat);
		for (unsigned int i = 51; i <= 53; i++)
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
	case 'r':
		camera_turn = 0;
		angle += 1.5f;
		break;
	case 'R':
		camera_turn = 0;
		angle -= 1.5f;
		break;
	case 'w': case 'W':
		print_location();
		way = 180.0f;

		if (move_z < -0.8f || (move_x >= -0.15f && move_x <= 0.15f && move_z <= 0.15f && move_z >= 0.14f)
			|| (move_x <= -0.48f && move_x >= -0.71f && move_z <= -0.45f && move_z >= -0.46f)
			|| (move_x <= 0.62f && move_x >= 0.55f && move_z >= -0.5f && move_z <= -0.45f))
			break;
		else
			move_z -= amount;


		break;
	case 'a': case 'A':
		print_location();
		way = -90.f;
		if (move_x < -0.8f || (move_z > 0.55f && move_x < -0.48f)
			|| (move_x <= 0.15f && move_x >= 0.14f && move_z >= -0.15f && move_z <= 0.15f)
			|| (move_x <= -0.47f && move_x >= -0.48f && move_z >= -0.78f && move_z <= -0.49f)
			|| (move_x <= 0.71f && move_x >= 0.7f && move_z < -0.45f))
			break;
		else
			move_x -= amount;
		break;
	case 's': case 'S':
		print_location();
		way = 0.0f;
		if (move_z > 0.8f || (move_z >= 0.54f && move_z <= 0.55f && (move_x > 0.55f || move_x < -0.55f))
			|| (move_x >= -0.15f && move_x <= 0.15f && move_z <= -0.15f && move_z >= -0.14f)
			|| (move_x <= -0.48f && move_x >= -0.71f && move_z <= -0.78f && move_z >= -0.79f))
			break;
		else
			move_z += amount;
		break;
	case 'd': case 'D':
		print_location();
		way = 90.0f;
		if (move_x > 0.8f || (move_z > 0.55f && move_x > 0.55f)
			|| (move_x <= -0.14f && move_x >= -0.15f && move_z >= -0.15f && move_z <= 0.15f)
			|| (move_x <= -0.70f && move_x >= -0.71f && move_z >= -0.78f && move_z <= -0.49f)
			|| (move_x <= 0.5f && move_x >= 0.49f && move_z < -0.45f))
			break;
		else
			move_x += amount;
		break;
	case 'j': case 'J':
		jump = 0.02f;
		break;
	case 'p': case 'P':
		trigger = true;
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

void Example::print_location()
{
	std::cout << "(X, Z) : " << move_x << " " << move_z << std::endl;
}

bool Example::setTimer()
{	
	if (door < 1.0f) door += door_move;

	if (trigger)
	{
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
		bench += bench_rotate;
		if (bench >= 45.0f || bench < 0.0f) bench_rotate *= -1.0f;

		bench_bar -= bench_bar_amount;
		if (bench_bar < -0.02f || bench_bar >= 0.0f) bench_bar_amount *= -1.0f;
	}	
	
	return true;
}


