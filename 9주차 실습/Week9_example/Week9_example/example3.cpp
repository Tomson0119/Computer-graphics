#include "Example3.h"
#include "sphere.h"
#include "rectangle.h"
#include "pyramid.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Example3::Example3(int window_w, int window_h)
{
	lightShader = new Shader();
	lampShader = new Shader();
	camera = new Camera(window_w, window_h);

	lightPos = vec3(2.0f, 1.0f, 0.0f);
	lightColor = vec3(1.0f);

	polygon_mode = GL_FILL;
	prev_time = 0, move_y = 0.01f;
	REvent = 0, SEvent = 0;

	objs.emplace_back(new Rect());
	objs.emplace_back(new Pyramid());
	objs.emplace_back(new Sphere());
	objs.emplace_back(new Sphere());
	objs.emplace_back(new Sphere());
	objs.emplace_back(new Sphere());

	float Low = -2.0f, High = 2.0f;
	for (int i = 0; i < raindrops; i++)
	{
		float x = Low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (High - Low)));
		float z = Low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (High - Low)));
		
		poses.push_back(vec2(x, z));
	}

	light_bulb = new Sphere();
}

Example3::~Example3()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

	delete light_bulb;
	delete lightShader;
	delete lampShader;
	delete camera;
}

void Example3::init()
{
	lightShader->make_shader("light.vs", "light.fs");
	lampShader->make_shader("lamp.vs", "lamp.fs");

	camera->translateCameraPos(1.f, 1.0f, 0.0f);

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
	light_bulb->setVertexArray();

	objs.at(0)->setWorldTranslate(0.0f, -0.2f, 0.0f);
	objs.at(0)->setWorldRotate(90.0f, 1.0f, 0.0f, 0.0f);
	objs.at(0)->setWorldScale(10.0f);

	objs.at(1)->setWorldTranslate(0.0f, 0.2f, 0.0f);
	objs.at(1)->setWorldScale(2.0f);

	objs.at(2)->setPos(-0.3f, 0.6f, 0.0f);
	objs.at(3)->setPos(-0.8f, 0.6f, 0.0f);
	objs.at(4)->setPos(-1.4f, 0.6f, 0.0f);
	objs.at(5)->setPos(0.0f, 1.0f, 0.0f);
}

void Example3::draw()
{
	// Objects
	lightShader->use_program();

	lightShader->setMat4("view", camera->getViewMat());
	lightShader->setMat4("proj", camera->getProjMat());
	lightShader->setVec3("lightColor", lightColor);
	lightShader->setVec3("lightPos", lightPos);
	lightShader->setVec3("viewPos", camera->getPosition());

	lightShader->setVec3("objectColor", vec3(0.5f));
	objs.at(0)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(1.0f, 1.0f, 0.0f));
	objs.at(1)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	objs.at(2)->setWorldMat(1.0f);
	objs.at(2)->translateToPos();
	objs.at(2)->setWorldScale(0.1f);
	objs.at(2)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
	objs.at(3)->setWorldMat(1.0f);
	objs.at(3)->translateToPos();
	objs.at(3)->setWorldScale(0.2f);
	objs.at(3)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
	objs.at(4)->setWorldMat(1.0f);
	objs.at(4)->translateToPos();
	objs.at(4)->setWorldScale(0.3f);
	objs.at(4)->draw(lightShader);


	lightShader->setVec3("objectColor", vec3(0.0f, 1.0f, 1.0f));
	for (int i = 0; i < raindrops; i++)
	{
		float x = poses.at(i).x;
		float z = poses.at(i).y;

		objs.at(5)->setWorldMat(1.0f);
		objs.at(5)->setWorldTranslate(x, objs.at(5)->getPos().y, z);
		objs.at(5)->setWorldScale(0.05f);
		objs.at(5)->draw(lightShader);
	}	

	// Light Bulb
	lampShader->use_program();
	light_bulb->setWorldMat(mat4(1.0f));
	light_bulb->setWorldTranslate(lightPos);
	light_bulb->setWorldScale(vec3(0.1f));
	lampShader->setMat4("view", camera->getViewMat());
	lampShader->setMat4("proj", camera->getProjMat());

	light_bulb->draw(lampShader);
}

void Example3::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: case 'q': case 'Q':
		glutDestroyWindow(glutGetWindow());
		exit(0);

	case 'w': case 'W':
		polygon_mode = (polygon_mode == GL_FILL) ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;

	case 'r': case 'R':
		REvent = (REvent < 2) ? REvent += 1 : 0;
		break;

	case 's': case 'S':
		SEvent = (SEvent == 0) ? 1 : 0;
		break;

	case 'y': case 'Y':
		camera->rotateCameraPos(0.5f, 0.0f, 1.0f, 0.0f);
		break;
	}
}

void Example3::setTimer()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	int delta_time = time - prev_time;
	if (delta_time > 10) {
		float rotate_speed = 0.5f;

		objs.at(2)->setPosRotate(rotate_speed, 0.0f, 1.0f, 0.0f);
		objs.at(3)->setPosRotate(rotate_speed / 1.5f, 0.0f, 1.0f, 0.0f);
		objs.at(4)->setPosRotate(rotate_speed / 2.0f, 0.0f, 1.0f, 0.0f);

		if (REvent > 0)
		{
			float angle = (REvent == 1) ? rotate_speed : -rotate_speed;
			lightPos = rotate(lightPos, radians(angle), vec3(0.0f, 0.0f, 1.0f));
		}

		if (SEvent)
		{
			if (objs.at(5)->getPos().y >= 1.0f ||
				objs.at(5)->getPos().y <= 0.0f)
				move_y *= -1.0f;
			objs.at(5)->setPos(objs.at(5)->getPos() + vec3(0.0f, move_y, 0.0f));
		}

		prev_time = time;
	}
}
