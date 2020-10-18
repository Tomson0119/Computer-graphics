#include "example.h"
#include "cube.h"
#include "pyramid.h"
#include "line.h"
#include "sphere.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Example::Example()
	: angle(0.0f), polygon_mode(GL_FILL), example_scene(1), 
	  rotate(0.0f), orbit(0.0f), small_orbit(0.0f)
{
	shader = new Shader();

	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);

	// Insert objects
	{
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
	// Initialize curObj
	curObj = nullptr;
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
	shader->make_shader("vertex.glsl", "fragment.glsl");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Initialize View, Projection Matrix
	viewMat = glm::lookAt(glm::vec3(0.0f, 0.2f, 4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projMat = glm::perspective(glm::radians(45.0f), 
		(float)window_w / (float)window_h, 0.1f, 100.0f);

	// Set Object's location
	for (unsigned int i = 3; i < objs.size(); i++)
	{
		if (i == 6)
			objs.at(i)->setWorldScale(glm::vec3(0.6f, 0.6f, 0.6f));
		else if (i != 6 && i < 10) {
			objs.at(i)->setWorldTranslate(glm::vec3(-1.0f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(0.3f, 0.3f, 0.3f));
		}
		else if (i != 6 && i < objs.size()) {
			objs.at(i)->setWorldTranslate(glm::vec3(-0.3f, 0.0f, 0.0f));
			objs.at(i)->setWorldScale(glm::vec3(0.1f, 0.1f, 0.1f));
		}
	}		
}

void Example::sceneOne_draw()
{
	shader->setViewTransform(viewMat);
	shader->setProjTransform(projMat);
	
	glm::mat4 mat = glm::mat4(1.0f);
	//mat = glm::rotate(mat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
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

		break;
	}
}

void Example::sceneTwo_key_event(unsigned char key, int x, int y)
{
}

bool Example::setTimer()
{	
	small_orbit += rotate_speed * 2.0f;
	orbit += rotate_speed;
	angle += rotate / 2.0f;
	return true;
}
