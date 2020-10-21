#include "example.h"
#include "line.h"
#include "sphere.h"
#include "triangle.h"
#include "rectangle.h"
#include "cube.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>


Example::Example()
	: angle(0.0f), polygon_mode(GL_FILL),
	example_scene(3), project_mode(0),
	rotate(0.0f), orbit(0.0f), small_orbit(0.0f),
	up_rotate(0.0f), front_rotate(0.0f),
	up_angle(0.0f), front_angle(0.0f),
	bottom_angle(0.0f), bottom_rotate(0.0f),
	mid_angle(0.0f), mid_rotate(0.0f),
	top_angle(0.0f), top_rotate(0.0f),
	move(0.0f), move_x(0.0f),
	window_w(0), window_h(0), draw_mode(0)
{
	shader = new Shader();

	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);

	{ // Insert Object For Example 1
		// Big Orbits 0 ~ 2
		objs.emplace_back(new Line("circle"));
		objs.emplace_back(new Line("circle"));
		objs.emplace_back(new Line("circle"));

		// Small Orbits 3 ~ 5
		objs.emplace_back(new Line("circle"));
		objs.emplace_back(new Line("circle"));
		objs.emplace_back(new Line("circle"));

		// Sun 6
		objs.emplace_back(new Sphere("red"));

		// Planet 7 ~ 9
		objs.emplace_back(new Sphere("green"));
		objs.emplace_back(new Sphere("green"));
		objs.emplace_back(new Sphere("green"));

		// Satelite 10 ~ 12
		objs.emplace_back(new Sphere("gray"));
		objs.emplace_back(new Sphere("gray"));
		objs.emplace_back(new Sphere("gray"));
	}

	{ // Insert Object For Example 2
		// Line 13 ~ 15
		objs.emplace_back(new Line("x"));
		objs.emplace_back(new Line("y"));
		objs.emplace_back(new Line("z"));

		// Cube 16 ~ 21
		objs.emplace_back(new Rect("red"));
		objs.emplace_back(new Rect("blue"));
		objs.emplace_back(new Rect("green"));
		objs.emplace_back(new Rect("yellow"));
		objs.emplace_back(new Rect("purple"));
		objs.emplace_back(new Rect("sky"));

		// Pyramid 22 ~ 26
		objs.emplace_back(new Rect("yellow"));
		objs.emplace_back(new Triangle("red"));
		objs.emplace_back(new Triangle("green"));
		objs.emplace_back(new Triangle("blue"));
		objs.emplace_back(new Triangle("purple"));
	}

	{ // Insert Crane Objects
		crane.emplace_back(new Rect("gray"));
		crane.emplace_back(new Cube("red"));
		crane.emplace_back(new Cube("yellow"));
		crane.emplace_back(new Cube("sky"));
		crane.emplace_back(new Cube("sky"));
	}
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

	for (auto object : crane)
		delete object;
	std::vector<Object*>().swap(crane);

	delete shader;
}

void Example::sceneOne_init()
{
	// Initialize View Matrix
	viewMat = glm::lookAt(camera.Position, camera.Direction, camera.Up);

	// Initialize Projection Matrix
	projMat = glm::perspective(glm::radians(45.0f),
		(float)window_w / (float)window_h, 0.1f, 50.0f);

	angle = 0.0f;
	rotate = 0.0f;
	orbit = 0.0f;
	small_orbit = 0.0f;

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setWorldMat(glm::mat4(1.0f));

	// Set Object's location
	for (unsigned int i = 3; i < 13; i++)
	{
		if (i == 6)
			objs.at(i)->setWorldScale(glm::vec3(0.6f, 0.6f, 0.6f));
		else if (i != 6 && i < 10) {
			objs.at(i)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(0.3f, 0.3f, 0.3f));
		}
		else if (i != 6 && i < 13) {
			objs.at(i)->setWorldTranslate(glm::vec3(-0.3f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.1f));
		}
	}
}

void Example::sceneTwo_init()
{
	angle = 0.0f;
	rotate = 0.0f;
	up_angle = 0.0f;
	up_rotate = 0.0f;
	front_angle = 0.0f;
	front_rotate = 0.0f;
	draw_mode = 0;
	project_mode = 0;
	polygon_mode = GL_FILL;

	// Initialize View Matrix
	viewMat = glm::lookAt(camera.Position, camera.Direction, camera.Up);

	// Initialize Projection Matrix
	projMat = glm::perspective(glm::radians(45.0f),
		(float)window_w / (float)window_h, 0.1f, 50.0f);

	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, 1.5f));
	viewMat = glm::rotate(viewMat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::rotate(viewMat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setWorldMat(glm::mat4(1.0f));

	for (unsigned int i = 16; i < objs.size(); i++)
	{
		// Rect
		if (i == 16)
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.0f, -0.2f));
		else if (i < 19)
		{
			if (i == 17)
				objs.at(i)->setWorldTranslate(glm::vec3(-0.2f, 0.0f, 0.0f));
			else
				objs.at(i)->setWorldTranslate(glm::vec3(0.2f, 0.0f, 0.0f));
			objs.at(i)->setWorldRotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (i < 21)
		{
			if (i == 19)
				objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -0.2f, 0.0f));
			objs.at(i)->setWorldRotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (i == 21)
			objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.2f, 0.0f));
		else {
			// Trianlge
			if (i == 22)
			{
				objs.at(i)->setWorldTranslate(glm::vec3(0.0f, -0.2f, 0.0f));
				objs.at(i)->setWorldRotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else
			{
				objs.at(i)->setWorldRotate(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				objs.at(i)->setWorldTranslate(glm::vec3(0.0f, 0.2f, 0.0f));
			}
		}
	}
}

void Example::sceneThree_init()
{
	// Initialize View Matrix
	viewMat = glm::lookAt(camera.Position, camera.Direction, camera.Up);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, -0.5f, 0.0f));

	// Initialize Projection Matrix
	projMat = glm::perspective(glm::radians(45.0f),
		(float)window_w / (float)window_h, 0.1f, 50.0f);

	angle = 0.0f, rotate = 0.0f;
	bottom_angle = 0.0f, bottom_rotate = 0.0f;
	mid_angle = 0.0f, mid_rotate = 0.0f;
	top_angle = 0.0f, top_rotate = 0.0f;

	for (unsigned int i = 0; i < crane.size(); i++)
		crane.at(i)->setWorldMat(glm::mat4(1.0f));

	crane.at(0)->setWorldTranslate(glm::vec3(0.0f, -0.2f, 0.0f));
	crane.at(0)->setWorldRotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	crane.at(0)->setWorldScale(glm::vec3(10.0f, 10.0f, 10.0f));

	crane.at(1)->setWorldScale(glm::vec3(1.0f, 0.3f, 1.0f));
	
	crane.at(2)->setWorldScale(glm::vec3(0.6f, 0.4f, 0.6f));
	crane.at(2)->setWorldTranslate(glm::vec3(0.0f, 0.3f, 0.0f));

	crane.at(3)->setWorldScale(glm::vec3(0.1f, 0.5f, 0.1f));
	crane.at(3)->setWorldTranslate(glm::vec3(-0.4f, 0.1f, 0.0f));

	crane.at(4)->setWorldScale(glm::vec3(0.1f, 0.5f, 0.1f));
	crane.at(4)->setWorldTranslate(glm::vec3(0.4f, 0.1f, 0.0f));
}

void Example::init(int window_w, int window_h)
{
	this->window_w = window_w;
	this->window_h = window_h;

	shader->make_shader("vertex.glsl", "fragment.glsl");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
	for (unsigned int i = 0; i < crane.size(); i++)
		crane.at(i)->setVertexArray();


	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);	

	if (example_scene == 1)
		sceneOne_init();
	else if (example_scene == 2)
		sceneTwo_init();
	else
		sceneThree_init();
}

void Example::sceneOne_draw()
{
	shader->setViewTransform(viewMat);
	shader->setProjTransform(projMat);
	
	glm::mat4 mat = glm::mat4(1.0f);
	shader->setOutWorldTransform(mat);

	// Sun
	objs.at(6)->setWorldRotate(rotate_speed, glm::vec3(0.0f, 1.0f, 0.0f));
	objs.at(6)->draw(shader);

	{ // Rotate 0.0f
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(orbit), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);

		objs.at(2)->draw(shader);
		objs.at(5)->draw(shader);
		objs.at(9)->draw(shader);

		mat = glm::translate(mat, glm::vec3(-1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(small_orbit), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);
		objs.at(12)->draw(shader);
	}

	{ // Rotate 45.0f
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::rotate(mat, glm::radians(orbit - 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);

		objs.at(1)->draw(shader);
		objs.at(4)->draw(shader);
		objs.at(8)->draw(shader);

		mat = glm::translate(mat, glm::vec3(-1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(small_orbit), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);
		objs.at(11)->draw(shader);
	}

	{ // Rotate -45.0f
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::rotate(mat, glm::radians(orbit + 20.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);

		objs.at(2)->draw(shader);
		objs.at(5)->draw(shader);
		objs.at(9)->draw(shader);

		mat = glm::translate(mat, glm::vec3(-1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(small_orbit), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setOutWorldTransform(mat);
		objs.at(12)->draw(shader);
	}
}

void Example::sceneTwo_draw()
{
	shader->setViewTransform(viewMat);
	shader->setProjTransform(projMat);

	// Idle
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setOutWorldTransform(mat);

	for (unsigned int i = 13; i < 16; i++)
		objs.at(i)->draw(shader);

	if (draw_mode == 0) {
		for (unsigned int i = 16; i < 20; i++)
			objs.at(i)->draw(shader);

		{ // Up Rect
			mat = glm::mat4(1.0f);
			mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			mat = glm::translate(mat, glm::vec3(0.0f, 0.2f, 0.0f));
			mat = glm::rotate(mat, glm::radians(up_angle), glm::vec3(1.0f, 0.0f, 0.0f));
			shader->setOutWorldTransform(mat);
			objs.at(20)->draw(shader);
		}

		{ // Front Rect		
			mat = glm::mat4(1.0f);
			mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			mat = glm::translate(mat, glm::vec3(0.0f, -0.2f, 0.2f));
			mat = glm::rotate(mat, glm::radians(front_angle), glm::vec3(1.0f, 0.0f, 0.0f));
			shader->setOutWorldTransform(mat);
			objs.at(21)->draw(shader);
		}
	}
	else 
	{
		objs.at(22)->draw(shader);

		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(0.2f, -0.2f, 0.0f));
		mat = glm::rotate(mat, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(front_angle), glm::vec3(1.0f, 0.0f, 0.0f));

		shader->setOutWorldTransform(mat);
		objs.at(23)->draw(shader);

		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(-0.2f, -0.2f, 0.0f));
		mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(front_angle), glm::vec3(1.0f, 0.0f, 0.0f));

		shader->setOutWorldTransform(mat);
		objs.at(24)->draw(shader);

		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(0.0f, -0.2f, 0.2f));
		mat = glm::rotate(mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(front_angle), glm::vec3(1.0f, 0.0f, 0.0f));

		shader->setOutWorldTransform(mat);
		objs.at(25)->draw(shader);

		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(0.0f, -0.2f, -0.2f));
		mat = glm::rotate(mat, glm::radians(front_angle), glm::vec3(1.0f, 0.0f, 0.0f));

		shader->setOutWorldTransform(mat);
		objs.at(26)->draw(shader);
	}
}

void Example::sceneThree_draw()
{	
	viewMat = glm::lookAt(camera.Position, camera.Position + camera.Direction, camera.Up);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, -0.5f, 0.0f));

	shader->setViewTransform(viewMat);
	shader->setProjTransform(projMat);

	// Idle
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setOutWorldTransform(mat);
	crane.at(0)->draw(shader);

	// Bottom
	mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(move, 0.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(bottom_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setOutWorldTransform(mat);
	crane.at(1)->draw(shader);

	// Middle
	mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(move, 0.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(bottom_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(mid_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setOutWorldTransform(mat);
	crane.at(2)->draw(shader);

	// Top-left
	mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(move, 0.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(bottom_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(mid_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::translate(mat, glm::vec3(0.0f, 0.25f, 0.0f));
	mat = glm::rotate(mat, glm::radians(top_angle), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setOutWorldTransform(mat);
	crane.at(3)->draw(shader);

	// Top-right
	mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(move, 0.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(bottom_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, glm::radians(mid_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::translate(mat, glm::vec3(0.0f, 0.25f, 0.0f));
	mat = glm::rotate(mat, glm::radians(-top_angle), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setOutWorldTransform(mat);
	crane.at(4)->draw(shader);
}

void Example::draw()
{
	shader->use_program();
	
	if (example_scene == 1)
		sceneOne_draw();
	else if (example_scene == 2)
		sceneTwo_draw();
	else
		sceneThree_draw();
}

void Example::key_event(unsigned char key, int x, int y)
{
	if (key == 27 || key =='q' || key == 'Q')
	{
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}

	if (example_scene == 1)
		sceneOne_key_event(key, x, y);
	else if (example_scene == 2)
		sceneTwo_key_event(key, x, y);
	else
		sceneThree_key_event(key, x, y);
}

void Example::sceneOne_key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'z': case 'Z':
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, move_dist));
		break;
	case 'x': case 'X':
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -move_dist));
		break;
	case 'y': case 'Y':
		if (rotate <= 0.0f)
			rotate = rotate_speed;
		else
			rotate = -rotate_speed;
		break;
	case 'm': case 'M':
		if (polygon_mode == GL_LINE)
			polygon_mode = GL_FILL;
		else
			polygon_mode = GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;
	case 'w':
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, move_dist, 0.0f));
		break;
	case 'a':
		viewMat = glm::translate(viewMat, glm::vec3(-move_dist, 0.0f, 0.0f));
		break;
	case 's':
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, -move_dist, 0.0f));
		break;
	case 'd':
		viewMat = glm::translate(viewMat, glm::vec3(move_dist, 0.0f, 0.0f));
		break;
	case 50:
		example_scene = 2;
		sceneTwo_init();
		break;
	}
}

void Example::sceneTwo_key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y': case 'Y':
		if (rotate <= 0.0f)
			rotate = rotate_speed;
		else
			rotate = 0.0f;
		break;
	
	case 't': case 'T':
		if (up_rotate <= 0.0f)
			up_rotate = rotate_speed;
		else
			up_rotate = 0.0f;
		break;
	case 'f': case 'F':
		if (front_rotate == 0.0f)
			front_rotate = rotate_speed;
		else 
			front_rotate = 0.0f;
		break;
	case 'p': case 'P':
		if (project_mode == 0)
		{
			projMat = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 50.f);
			project_mode = 1;
		}
		else
		{
			projMat = glm::perspective(glm::radians(45.0f),
				(float)window_w / (float)window_h, 0.1f, 50.0f);
			project_mode = 0;
		}
		break;
	case 'm': case 'M':
		if (polygon_mode == GL_LINE)
			polygon_mode = GL_FILL;
		else
			polygon_mode = GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;
	case 'c': case 'C':
		draw_mode = (draw_mode > 0) ? 0 : 1;
		up_angle = 0.0f;
		up_rotate = 0.0f;
		front_angle = 0.0f;
		front_rotate = 0.0f;
		angle = 0.0f;
		rotate = 0.0f;
		break;
	case 'o': case 'O':
		if (front_rotate == 0.0f)
			front_rotate = -rotate_speed;
		else
			front_rotate = 0.0f;
		break;
		break;
	case 49:
		example_scene = 1;
		sceneOne_init();
		break;
	}
}

void Example::sceneThree_key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y': case 'Y':
		if (rotate <= 0.0f)
			rotate = rotate_speed;
		else
			rotate = 0.0f;
		break;
	case 'b': case 'B':
		if (bottom_rotate <= 0.0f)
			bottom_rotate = rotate_speed;
		else
			bottom_rotate = -rotate_speed;
		break;
	case 'm': case 'M':
		if (mid_rotate <= 0.0f)
			mid_rotate = rotate_speed;
		else
			mid_rotate = -rotate_speed;
		break;
	case 't': case 'T':
		if (top_rotate <= 0.0f)
			top_rotate = rotate_speed;
		else
			top_rotate = -rotate_speed;
		break;
	case 'g': case 'G':
		if (move_x <= 0.0f)
			move_x = move_dist;
		break;
	case 's': case 'S':
		rotate = 0.0f;
		bottom_rotate = 0.0f;
		mid_rotate = 0.0f;
		top_rotate = 0.0f;
		move_x = 0.0f;
		break;
	case 'c': case 'C':
		angle = 0.0f;
		bottom_angle = 0.0f;
		mid_angle = 0.0f;
		top_angle = 0.0f;
		move = 0.0f;

		rotate = 0.0f;
		bottom_rotate = 0.0f;
		mid_rotate = 0.0f;
		top_rotate = 0.0f;
		move_x = 0.0f;
		break;
	case 'z': 
		camera.Position += glm::vec3(0.0f, 0.0f, move_dist);
		break;
	case 'Z':
		camera.Position += glm::vec3(0.0f, 0.0f, -move_dist);
		break;
	case 'x':
		camera.Position += glm::vec3(move_dist, 0.0f, 0.0f);
		break;
	case 'X':
		camera.Position += glm::vec3(-move_dist, 0.0f, 0.0f);
		break;
	case 'r': case 'R':
		camera.Direction = glm::rotate(camera.Direction, glm::radians(3.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
		break;
	case 'w': case 'W':
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
	// For Every Scene
	angle += rotate / 2.0f;

	// For Scene 1
	small_orbit += rotate_speed * 2.0f;
	orbit += rotate_speed;
	
	// For Scene 2
	up_angle += up_rotate;
	front_angle += front_rotate;
	if (draw_mode == 0 && (front_angle >= 90.0f || front_angle < 0.0f)) front_rotate *= -1;
	else if(draw_mode == 1 && (front_angle <= -120.0f || front_angle > 0.0f)) front_rotate *= -1;

	// For Scene 3
	bottom_angle += bottom_rotate;
	mid_angle += mid_rotate;
	top_angle += top_rotate;
	if (top_angle >= 90.0f || top_angle <= -90.0f) top_rotate *= -1;
	move += move_x;
	if (move >= 1.0f || move <= -1.0f) move_x *= -1;

	return true;
}
