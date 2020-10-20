#include "example.h"
#include "line.h"
#include "sphere.h"
#include "triangle.h"
#include "rectangle.h"


#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Example::Example()
	: angle(0.0f), polygon_mode(GL_FILL), 
	  example_scene(1), project_mode(0),
	  rotate(0.0f), orbit(0.0f), small_orbit(0.0f),
	  up_rotate(0.0f), front_rotate(0.0f),
	  up_angle(0.0f), front_angle(0.0f),
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
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

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

void Example::init(int window_w, int window_h)
{
	this->window_w = window_w;
	this->window_h = window_h;

	shader->make_shader("vertex.glsl", "fragment.glsl");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);	

	if (example_scene == 1)
		sceneOne_init();
	else
		sceneTwo_init();
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

bool Example::setTimer()
{	
	small_orbit += rotate_speed * 2.0f;
	orbit += rotate_speed;
	angle += rotate / 2.0f;
	up_angle += up_rotate;

	front_angle += front_rotate;
	if (draw_mode == 0 && (front_angle >= 90.0f || front_angle < 0.0f)) front_rotate *= -1;
	else if(draw_mode == 1 && (front_angle <= -120.0f || front_angle > 0.0f)) front_rotate *= -1;


	return true;
}
