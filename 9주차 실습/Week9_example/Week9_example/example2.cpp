#include "example2.h"
#include "sphere.h"
#include "rectangle.h"
#include "cube.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Example2::Example2(int window_w, int window_h)
{
	lightShader = new Shader();
	lampShader = new Shader();
	camera = new Camera(window_w, window_h);

	lightPos = vec3(2.0f, 1.0f, 0.0f);
	lightColor = vec3(1.0f);

	polygon_mode = GL_FILL;
	prev_time = 0;
	REvent = 0;

	crane.emplace_back(new Rect());
	crane.emplace_back(new Cube());
	crane.emplace_back(new Cube());
	crane.emplace_back(new Cube());
	crane.emplace_back(new Cube());

	light_bulb = new Sphere();
}

Example2::~Example2()
{
	for (auto object : crane)
		delete object;
	std::vector<Object*>().swap(crane);

	delete light_bulb;
	delete lightShader;
	delete lampShader;
	delete camera;
}

void Example2::init()
{
	lightShader->make_shader("light.vs", "light.fs");
	lampShader->make_shader("lamp.vs", "lamp.fs");

	camera->translateCameraPos(0.0f, 0.5f, 0.0f);

	for (unsigned int i = 0; i < crane.size(); i++)
		crane.at(i)->setVertexArray();
	light_bulb->setVertexArray();

	crane.at(0)->setWorldTranslate(vec3(0.0f, -0.2f, 0.0f));
	crane.at(0)->setWorldRotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
	crane.at(0)->setWorldScale(glm::vec3(10.0f, 10.0f, 10.0f));

	crane.at(1)->setWorldScale(vec3(1.0f, 0.3f, 1.0f));

	crane.at(2)->setWorldScale(vec3(0.6f, 0.4f, 0.6f));
	crane.at(2)->setWorldTranslate(vec3(0.0f, 0.3f, 0.0f));

	crane.at(3)->setWorldScale(vec3(0.1f, 0.5f, 0.1f));
	crane.at(3)->setWorldTranslate(vec3(-0.4f, 0.6f, 0.0f));

	crane.at(4)->setWorldScale(vec3(0.1f, 0.5f, 0.1f));
	crane.at(4)->setWorldTranslate(vec3(0.4f, 0.6f, 0.0f));
}

void Example2::draw()
{
	// Crane
	lightShader->use_program();

	lightShader->setMat4("view", camera->getViewMat());
	lightShader->setMat4("proj", camera->getProjMat());
	lightShader->setVec3("lightColor", lightColor);
	lightShader->setVec3("lightPos", lightPos);
	lightShader->setVec3("viewPos", camera->getPosition());

	lightShader->setVec3("objectColor", vec3(0.5f));
	crane.at(0)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
	crane.at(1)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
	crane.at(2)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	crane.at(3)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	crane.at(4)->draw(lightShader);



	// Light Bulb
	lampShader->use_program();
	light_bulb->setWorldMat(mat4(1.0f));
	light_bulb->setWorldTranslate(lightPos);
	light_bulb->setWorldScale(vec3(0.1f));
	lampShader->setMat4("view", camera->getViewMat());
	lampShader->setMat4("proj", camera->getProjMat());

	light_bulb->draw(lampShader);
}

void Example2::key_event(unsigned char key, int x, int y)
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

	case 'y': case 'Y':
		camera->rotateCameraPos(0.5f, 0.0f, 1.0f, 0.0f);
		break;

	case 'm': case 'M':
		lightColor = (lightColor == vec3(1.0f))	? vec3(0.0f) : vec3(1.0f);
		break;

	case 'c': case 'C':
		if (lightColor == vec3(1.0f) || lightColor == vec3(0.0f))
			lightColor = vec3(1.0f, 0.0f, 0.0f);
		else if (lightColor == vec3(1.0f, 0.0f, 0.0f))
			lightColor = vec3(0.0f, 1.0f, 0.0f);
		else if (lightColor == vec3(0.0f, 1.0f, 0.0f))
			lightColor = vec3(0.0f, 0.0f, 1.0f);
		else if (lightColor == vec3(0.0f, 0.0f, 1.0f))
			lightColor = vec3(1.0f);
		break;

	case 's': case 'S':
		REvent = 0;
		break;

	case 'z':
		camera->translateCameraPos(0.0f, 0.0f, -0.1f);		
		break;

	case 'Z':
		camera->translateCameraPos(0.0f, 0.0f, 0.1f);
		break;

	case 'x':
		camera->translateCameraPos(-0.1f, 0.0f, 0.0f);
		break;

	case 'X':
		camera->translateCameraPos(0.1f, 0.0f, 0.0f);
		break;

	case 'k': case 'K':
		camera->rotateCameraCenter(1.5f, 0.0f, 1.0f, 0.0f);
		break;
	}
}

void Example2::setTimer()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	int delta_time = time - prev_time;
	if (delta_time > 10) {
		float rotate_speed = 0.5f;

		if (REvent > 0)
		{
			float angle = (REvent == 1) ? rotate_speed : -rotate_speed;
			lightPos = rotate(lightPos, radians(angle), vec3(0.0f, 1.0f, 0.0f));
		}
		
		prev_time = time;
	}
}
