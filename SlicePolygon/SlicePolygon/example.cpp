#include "example.h"
#include "triangle.h"
#include "line.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Example::Example(int window_w, int window_h)
{
	shader = new Shader();
	camera = new Camera(window_w, window_h);

	polygon_mode = GL_FILL;
	animation = true;
	prev_time = 0;

	begin = vec2(0.0f);
	temp = vec2(0.0f);
	end = vec2(0.0f);
	
	objs = std::vector<Object*>();
	line = nullptr;
}

Example::~Example()
{
	for (Object* obj : objs)
		delete obj;
	objs.clear();

	delete line;
	delete shader;
	delete camera;
}

void Example::init()
{
	shader->make_shader("object.vs", "object.fs");

	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->setVertexArray();
}

void Example::draw()
{
	shader->use_program();

	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	if (line != nullptr) line->draw(shader);

	shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->draw(shader);	
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
	}
}

void Example::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		begin = convert_xy(x, y);
		std::cout << "begin pos : " << begin.x << " " << begin.y << std::endl;
		line = new Line(begin);
	}
	else if (state == GLUT_UP)
	{
		line = nullptr;
		end = temp;
		std::cout << "end pos : " << end.x << " " << end.y << std::endl;
	}
}

void Example::motion_event(int x, int y)
{
	temp = convert_xy(x, y);
	line->changePos(temp);
	std::cout << "motion pos : " << temp.x << " " << temp.y << std::endl;
}

void Example::setTimer()
{
	if (animation)
	{
		int time = glutGet(GLUT_ELAPSED_TIME);
		int delta_time = time - prev_time;
		
		if (delta_time > 10) {
			for (unsigned int i = 0; i < objs.size(); i++) {
				objs.at(i)->setWorldTranslate(-0.01f, 0.0f, 0.0f);
				if (objs.at(i)->getPos().x < -1.3f)
				{
					objs.erase(objs.begin());
					std::cout << "Deleted : Triangle" << std::endl;
				}
			}
			
		}
		if (delta_time > 2000)
		{
			objs.push_back(new Triangle());
			objs.at(objs.size() - 1)->setWorldTranslate(1.3f, 0.5f, 0.0f);
			std::cout << "Pushed : Triangle" << objs.size() << std::endl;
			
			prev_time = time;
		}
	}
}

glm::vec2 Example::convert_xy(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	float pos_x = static_cast<float>(x - width / 2) /
		static_cast<float>(width / 2);

	float pos_y = static_cast<float>(height / 2 - y) /
		static_cast<float>(height / 2);

	return glm::vec2(pos_x, pos_y);
}