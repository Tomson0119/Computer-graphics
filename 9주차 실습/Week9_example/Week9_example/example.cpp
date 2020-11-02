#include "example.h"
#include "sphere.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace glm;

Example::Example(int window_w, int window_h)
{
	lightShader = new Shader();
	lampShader = new Shader();
	camera = new Camera(window_w, window_h);

	lightPos = vec3(2.0f, 0.0f, 0.0f);

	polygon_mode = GL_FILL;

	objs.push_back(new Sphere());
	objs.push_back(new Sphere());
	objs.push_back(new Sphere());

	light_bulb = new Sphere();
}

Example::~Example()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);

	delete light_bulb;
	delete lightShader;
	delete lampShader;
	delete camera;
}

void Example::init()
{
	lightShader->make_shader("light.vs", "light.fs");
	lampShader->make_shader("lamp.vs", "lamp.fs");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
	light_bulb->setVertexArray();

	objs.at(0)->setWorldTranslate(1.0f, 0.0f, 0.0f);
	objs.at(1)->setWorldTranslate(-0.3f, 0.0f, 0.0f);
	objs.at(1)->setWorldScale(0.5f, 0.5f, 0.5f);	
	objs.at(2)->setWorldTranslate(-1.2f, 0.0f, 0.0f);
	objs.at(2)->setWorldScale(0.3f, 0.3f, 0.3f);	
}

void Example::draw()
{
	// Spheres
	lightShader->use_program();

	lightShader->setMat4("view", camera->getViewMat());
	lightShader->setMat4("proj", camera->getProjMat());	
	lightShader->setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
	lightShader->setVec3("lightPos", lightPos);
	lightShader->setVec3("viewPos", camera->getPosition());

	lightShader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	objs.at(0)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
	objs.at(1)->draw(lightShader);

	lightShader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
	objs.at(2)->draw(lightShader);


	// Light Bulb
	lampShader->use_program();
	light_bulb->setWorldMat(mat4(1.0f));
	light_bulb->setWorldTranslate(lightPos);
	light_bulb->setWorldScale(vec3(0.1));
	lampShader->setMat4("view", camera->getViewMat());
	lampShader->setMat4("proj", camera->getProjMat());
	
	light_bulb->draw(lampShader);
}

void Example::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: case 'q': case 'Q':
		glutDestroyWindow(glutGetWindow());
		exit(0);

	case 'm': case 'M':
		polygon_mode = (polygon_mode == GL_FILL) ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;

	case 'r': case 'R':
		lightPos = lightPos + vec3(-0.1f, 0.0f, 0.0f);
		lightPos = rotate(lightPos, radians(1.5f), vec3(0.0f, 1.0f, 0.0f));
		lightPos = lightPos + vec3(0.1f, 0.0f, 0.0f);
		break;

	case 'c': case 'C':
		break;
	}
}

void Example::setTimer()
{
}
