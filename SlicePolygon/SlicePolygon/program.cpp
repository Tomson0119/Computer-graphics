#include "program.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Program::Program(int window_w, int window_h)
{
	shader = new Shader();
	camera = new Camera(window_w, window_h);
	util = new Util();

	polygon_mode = GL_FILL;
	animation = true;
	prev_time = 0;	
	
	objs = std::vector<Poly*>();
	boxes = std::vector<Poly*>();
	lines = std::vector<Line*>();

	playerLine = nullptr;
}

Program::~Program()
{
	for (Poly* obj : objs)
		delete obj;
	std::vector<Poly*>().swap(objs);

	for (Poly* obj : boxes)
		delete obj;
	std::vector<Poly*>().swap(boxes);

	for (Line* line : lines)
		delete line;
	std::vector<Line*>().swap(lines);

	delete playerLine;
	delete shader;
	delete camera;
	delete util;
}

void Program::init()
{
	shader->make_shader("object.vs", "object.fs");

	// for collision check debug
	objs.push_back(new Poly());
	vec4 bb = objs.at(objs.size() - 1)->getBoundBox();
	boxes.push_back(new Poly(bb));

	objs.at(objs.size() - 1)->translateWorld(0.0f, 0.3f);
	boxes.at(objs.size() - 1)->translateWorld(0.0f, 0.3f);
}

void Program::draw()
{
	shader->use_program();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Player Line
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	if (playerLine != nullptr) playerLine->draw(shader);

	// Lines
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < lines.size(); i++)
		lines.at(i)->draw(shader);

	// Objects
	shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->draw(shader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Bounding Box
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < boxes.size(); i++)
		boxes.at(i)->draw(shader);
}

void Program::key_event(unsigned char key, int x, int y)
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

void Program::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		playerLine = new Line(util->convert_xy(x, y));

	else if (state == GLUT_UP)
	{
		// Collision check
		for (unsigned int i = 0; i < objs.size(); i++)
		{
			int size = objs.at(i)->getVerticesSize();
			int intersect = 0;
			glm::vec2 points[2];

			for (int j = 0; j < size; j++)
			{
				std::cout << "Vertex : " << objs.at(i)->getVertex2(j).x
					<<", "<< objs.at(i)->getVertex2(j).y << std::endl;

				Line line = Line(objs.at(i)->getVertex2(j % size),
					objs.at(i)->getVertex2((j + 1) % size));

				// Check if line crosses polygon
				if (util->isIntersection(playerLine, &line))
				{
					// Get intersect point
					points[intersect++] = util->getIntersectPoint2(playerLine, &line);
				}

				if (intersect == 2) {
					std::cout << "Slice !" << std::endl;
					break;
				}
			}
			// delete polygon and push Two more polygon
			if (intersect == 2) {
				obj->
			}
		}
		
		playerLine = nullptr;
	}
}

void Program::motion_event(int x, int y)
{
	playerLine->changePos(util->convert_xy(x, y));
}

void Program::setTimer()
{
	if (animation)
	{
		int time = glutGet(GLUT_ELAPSED_TIME);
		int delta_time = time - prev_time;
		
		if (delta_time > 10) {
			//for (unsigned int i = 0; i < objs.size(); i++) {

			//	// Translate through line
			//	glm::vec2 end = lines.at(i)->getPoint2();
				/*objs.at(0)->translateAlong(vec2(-1.3f,0.2f), 0.01f);
				boxes.at(0)->translateAlong(vec2(-1.3f, 0.2f), 0.01f);*/

			//	if (objs.at(i)->getPos().x < -1.3f) // Erase Object out of sight
			//	{
			//		objs.erase(objs.begin()); // Erase Object
			//		boxes.erase(boxes.begin());
			//		lines.erase(lines.begin()); // Erase Line					
			//	}
			//}			
		}
		if (delta_time > 2000)
		{
			//// Insert New Object
			//objs.push_back(new Poly());
			//glm::vec4 bb = dynamic_cast<Poly*>(objs.at(objs.size() - 1))->getBoundBox();
			//boxes.push_back(new Poly(bb));
			//
			//// Insert Randomized Line
			//float begin_y = util->generateFloat(0.2f, 0.8f);
			//float end_y = util->generateFloat(0.2f, 0.8f);

			//glm::vec2 begin = glm::vec2(1.3f, begin_y);
			//glm::vec2 end = glm::vec2(-1.3f, end_y);

			//lines.push_back(new Line(begin, end));

			//// Translate Object To Up-Right
			//objs.at(objs.size() - 1)->setWorldTranslate(1.3f, begin_y, 0.0f);
			//boxes.at(objs.size() - 1)->setWorldTranslate(1.3f, begin_y, 0.0f);

			prev_time = time;
		}
	}
}

