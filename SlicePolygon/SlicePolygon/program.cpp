#include "program.h"
#include "triangle.h"
#include "line.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Program::Program(int window_w, int window_h)
{
	srand((unsigned int)time(0));

	shader = new Shader();
	camera = new Camera(window_w, window_h);
	random = new Random();

	polygon_mode = GL_FILL;
	animation = true;
	prev_time = 0;	
	
	objs = std::vector<Object*>();
	lines = std::vector<Line*>();

	playerLine = nullptr;
}

Program::~Program()
{
	for (Object* obj : objs)
		delete obj;
	std::vector<Object*>().swap(objs);

	for (Line* line : lines)
		delete line;
	std::vector<Line*>().swap(lines);

	delete playerLine;
	delete shader;
	delete camera;
}

void Program::init()
{
	shader->make_shader("object.vs", "object.fs");
}

void Program::draw()
{
	shader->use_program();

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
		playerLine = new Line(convert_xy(x, y));

	else if (state == GLUT_UP)
		playerLine = nullptr;
}

void Program::motion_event(int x, int y)
{
	playerLine->changePos(convert_xy(x, y));
}

void Program::setTimer()
{
	if (animation)
	{
		int time = glutGet(GLUT_ELAPSED_TIME);
		int delta_time = time - prev_time;
		
		if (delta_time > 10) {
			for (unsigned int i = 0; i < objs.size(); i++) {

				// Translate through line
				glm::vec2 end = lines.at(i)->getVertexEnd();
				objs.at(i)->translateAlong(end, 0.01f);

				if (objs.at(i)->getPos().x < -1.3f) // Erase Object out of sight
				{
					objs.erase(objs.begin()); // Erase Object
					lines.erase(lines.begin()); // Erase Line					
					//std::cout << "Deleted" << std::endl;
				}
			}			
		}
		if (delta_time > 2000)
		{
			// Insert New Object
			objs.push_back(new Triangle());
			
			// Insert Randomized Line
			float begin_y = random->generateFloat(0.2f, 0.8f);
			float end_y = random->generateFloat(0.2f, 0.8f);

			//std::cout << begin_y << " " << end_y << std::endl;
			glm::vec2 begin = glm::vec2(1.3f, begin_y);
			glm::vec2 end = glm::vec2(-1.3f, end_y);

			lines.push_back(new Line(begin, end));

			// Translate Object To Up-Right
			objs.at(objs.size() - 1)->setWorldTranslate(1.3f, begin_y, 0.0f);

			//std::cout << "Pushed : Triangle" << objs.size() << std::endl;
			
			prev_time = time;
		}
	}
}

glm::vec2 Program::convert_xy(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	float pos_x = static_cast<float>(x - width / 2) /
		static_cast<float>(width / 2);

	float pos_y = static_cast<float>(height / 2 - y) /
		static_cast<float>(height / 2);

	return glm::vec2(pos_x, pos_y);
}