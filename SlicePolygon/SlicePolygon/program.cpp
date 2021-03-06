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
	showLine = false;
	move_speed = 0.01f;

	prev_time = 0;	
	curr_time = 0;
	delta_time = 0;

	objs = std::vector<Poly*>();
	lines = std::vector<Line*>();
	net = std::vector<Line*>();

	captured = nullptr;
	playerLine = nullptr;
}

Program::~Program()
{
	for (Poly* obj : objs)
		delete obj;
	std::vector<Poly*>().swap(objs);

	for (Line* line : lines)
		delete line;
	std::vector<Line*>().swap(lines);

	for (Line* obj : net)
		delete obj;
	std::vector<Line*>().swap(net);

	delete captured;
	delete playerLine;
	delete shader;
	delete camera;
	delete util;
}

void Program::init()
{
	shader->make_shader("object.vs", "object.fs");

	// Initialize 24 net lines
	net.push_back(new Line(-1.3f, -0.4f, 1.3f, -0.4f));
	net.push_back(new Line(-1.3f, -0.6f, 1.3f, -0.6f));
	net.push_back(new Line(-1.3f, -0.8f, 1.3f, -0.8f));
	net.push_back(new Line(0.0f, -0.4f, 0.0f, -1.0f));
	net.push_back(new Line(-0.5f, -0.4f, -0.5f, -1.0f));
	net.push_back(new Line(-0.75f, -0.4f, -0.75f, -1.0f));
	net.push_back(new Line(-0.25f, -0.4f, -0.25f, -1.0f));
	net.push_back(new Line(0.5f, -0.4f, 0.5f, -1.0f));
	net.push_back(new Line(0.75f, -0.4f, 0.75f, -1.0f));
	net.push_back(new Line(0.25f, -0.4f, 0.25f, -1.0f));

	// Initialize each position of the net
	for (int i = 0; i <24; i++)
	{
		float x_increse = 0.25f * (i % 8);
		float y_increse = -0.2f * (i / 8);
		poses[i].set(-0.875f + x_increse, -0.5f + y_increse);

		if (i / 8 == 2)
			poses[i].active = true;
	}
}

void Program::draw()
{
	shader->use_program();

	// Player Line
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	if (playerLine != nullptr) playerLine->draw(shader);	

	// Objects
	shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < objs.size(); i++)
		objs.at(i)->draw(shader);

	// Lines
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	if (showLine) {
		for (unsigned int i = 0; i < lines.size(); i++)
			lines.at(i)->draw(shader);
	}

	// Net
	shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f));
	for (unsigned int i = 0; i < net.size(); i++)
		net.at(i)->draw(shader);
}

void Program::key_event(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: case 'q': case 'Q': // ESC or Q to exit
		glutDestroyWindow(glutGetWindow());
		exit(0);

	case 'm': case 'M': // Change Polygon Mode
		polygon_mode = (polygon_mode == GL_FILL) ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
		break;

	case 'o': case 'O': // Toggle showing lines
		showLine = !showLine;
		break;

	case '+': case '=': // Increase moving speed of polygons
		move_speed += 0.005f;
		break;

	case '-': case '_': // Decrese moving speed of polygons
		if (move_speed > 0.01f) move_speed -= 0.005f;
		break;
	}
}

void Program::mouse_event(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		vec2 mouse_pos = util->convert_xy(x, y);
		
		if(mouse_pos.y > -0.4f) // Create line when pos is above the -0.4f
			playerLine = new Line(util->convert_xy(x, y));
		else
		{
			// Get the centre position of selected net
			int index = isInside(mouse_pos, false);
			vec2 target = vec2(poses[index].pos_x, poses[index].pos_y);

			// return when theres no polygon
			if (poses[index].isEmpty) return;

			for (unsigned int i = 0; i < objs.size(); i++)
			{
				vec2 objPos = objs.at(i)->getPos();
		
				// If polygon is inside of the target net
				// Capture that polygon 
				if (objPos.x == target.x && objPos.y == target.y) {
					captured = objs.at(i);
					poses[index].active = true;
					poses[index].isEmpty = true;
					prev_position = target; // remember the previous position
					std::cout << "captured!" << std::endl;
				}
			}			
		}
	}

	else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		if (playerLine == nullptr) // Handle drag and drop event
		{
			if (captured == nullptr) return;

			int index = isInside(captured->getPos(), false);

			if (index >= 0)
			{
				if (poses[index].isEmpty) // If net is empty, put polygon inside
				{ 
					vec2 target = vec2(poses[index].pos_x, poses[index].pos_y);

					captured->translateWorld(target.x - captured->getPos().x,
						target.y - captured->getPos().y);
					poses[index].active = false;
					poses[index].isEmpty = false;

					// Activate net above if it's empty 
					if (index >= 8 && poses[index - 8].isEmpty)
						poses[index - 8].active = true;
					else if (index >= 16 && poses[index - 16].isEmpty)
						poses[index - 16].active = true;
				}
				else 
				{
					// If net is full return back to where it was
					captured->translateWorld(prev_position.x - captured->getPos().x,
						prev_position.y - captured->getPos().y);
				}
			}
			captured = nullptr;
		}

		else { // Handle slicing event
			int size = objs.size();
			std::vector<int> objIndices;
			for (int i = 0; i < size; i++)
			{
				// Check collision for every polygon exists
				// If collision happens, push index of polygon 
				if (collision_event(objs.at(i)))
					objIndices.push_back(i);
			}

			// Erase polygons by backwards
			for (unsigned int i = objIndices.size(); i > 0; i--) {
				objs.erase(objs.begin() + objIndices.at(i - 1));
				lines.erase(lines.begin() + objIndices.at(i - 1));

				std::cout << "Polygon deleted : Slice event" << std::endl;
			}

			playerLine = nullptr;
		}
	}
}

bool Program::collision_event(Poly* obj)
{
	int size = obj->getVerticesSize();
	int intersect = 0;
	glm::vec2 points[2];

	// Check collision for every line of polygon
	for (int j = 0; j < size; j++)
	{
		Line line = Line(obj->getVertex2(j % size),
			obj->getVertex2((j + 1) % size));

		// Check if line crosses polygon
		if (util->isIntersection(playerLine, &line))
		{
			// Get intersecting point
			points[intersect++] = util->getIntersectPoint2(playerLine, &line);
		}

		if (intersect == 2) {
			// Sort points by y value
			if (points[0].y > points[1].y)
				std::swap(points[0], points[1]);

			slice_polygon(obj, points);
			return true;
		}
	}
	return false;	
}

void Program::slice_polygon(Poly* obj, glm::vec2 points[])
{
	int size = obj->getVerticesSize();

	std::vector<vec2> left;
	std::vector<vec2> right;

	for (int j = 0; j < size; j++)
	{
		// Check if points are counter-clock-wise
		if (util->getPointPosition(points[0], points[1], obj->getVertex2(j)) > 0)
			// if points are ccw, then these are left side
			left.push_back(obj->getVertex2(j));
		else
			// if poitns are cw, these are right side
			right.push_back(obj->getVertex2(j));
	}

	// Push intersecting points
	left.push_back(points[0]);
	left.push_back(points[1]);
	right.push_back(points[0]);
	right.push_back(points[1]);

	// Sort vertexes ccw
	util->quickSort(left, 1, left.size() - 1);	
	util->quickSort(right, 1, right.size() - 1);

	objs.push_back(new Poly(left));
	lines.push_back(new Line(vec2(0.0f))); // Push temp line
	objs.at(objs.size() - 1)->FALL = true;
	
	objs.push_back(new Poly(right));
	lines.push_back(new Line(vec2(0.0f))); // Push temp line
	objs.at(objs.size() - 1)->FALL = true;
	objs.at(objs.size() - 1)->RIGHT = true;
}

void Program::motion_event(int x, int y)
{
	vec2 mouse_pos = util->convert_xy(x, y);
	if (playerLine != nullptr && mouse_pos.y > -0.4f)
		// Last vertex of line follows mouse cursor
		playerLine->changePos(mouse_pos);
	else
	{
		if (captured != nullptr)
			// Translate polygon to mouse cursor
			captured->translateWorld(mouse_pos.x - captured->getPos().x
				, mouse_pos.y - captured->getPos().y);
	}
}

bool Program::setTimer()
{
	curr_time = glutGet(GLUT_ELAPSED_TIME);
	delta_time = curr_time - prev_time;

	if (delta_time > 10) {
		
		for (unsigned int i = 0; i < objs.size(); i++) {
			
			if (!objs.at(i)->FALL) { // If it's not piece
				//Translate along the line
				glm::vec2 end = lines.at(i)->getPoint2();
				objs.at(i)->translateAlong(end, move_speed);				
			}
			else if(!objs.at(i)->FIXED) // Falling pieces
			{ 
				// Right sided polygon goes to right
				// Left sided polygon goes to left
				if (objs.at(i)->RIGHT)
					objs.at(i)->translateWorld(0.001f, -0.01f);
				else
					objs.at(i)->translateWorld(-0.001f, -0.01f);
				
				// Put polygons inside the net
				// if polygon's pos is inside of net position
				int index = isInside(objs.at(i)->getPos(), true);

				if (index >= 0)
				{
					vec2 end = vec2(poses[index].pos_x, poses[index].pos_y);

					// Do translate polygon to net position
					objs.at(i)->translateWorld(poses[index].pos_x - objs.at(i)->getPos().x,
						poses[index].pos_y - objs.at(i)->getPos().y);

					// Scale the polygon to fit into net size => failed 

					objs.at(i)->FIXED = true;
					poses[index].active = false;
					poses[index].isEmpty = false;

					// Activate net above if it's empty 
					if (index >= 8 && poses[index - 8].isEmpty)
						poses[index - 8].active = true;
					else if (index >= 16 && poses[index - 16].isEmpty)
						poses[index - 16].active = true;

					if (check_game_end()) { // If game ended returns false
						std::cout << "Game Finished" << std::endl;
						return false;
					}
				}
			}

			if (objs.at(i)->getPos().x < -1.3f || objs.at(i)->getPos().y < -1.0f) // Erase Object out of sight
			{
				std::cout << "Polygon erased! : Out of screen" << std::endl;
				objs.erase(objs.begin() + i); // Erase Object
				lines.erase(lines.begin() + i); // Erase Line					
			}
		}			
	}
	if (delta_time > 2000)
	{
		// Insert New Object
		objs.push_back(new Poly());
		
		// Insert Randomized Line
		float begin_y = util->generateFloat(0.2f, 0.8f);
		float end_y = util->generateFloat(0.2f, 0.8f);

		glm::vec2 begin = glm::vec2(1.3f, begin_y);
		glm::vec2 end = glm::vec2(-1.3f, end_y);

		lines.push_back(new Line(begin, end));

		// Translate Object To Up-Right
		objs.at(objs.size() - 1)->translateWorld(1.3f, begin_y);

		// reset prev_time
		prev_time = curr_time;
	}
	return true;
}

int Program::isInside(glm::vec2 position, bool checkActive)
{
	for (int i = 0; i < sizeof(poses) / sizeof(poses[0]); i++)
	{
		bool Active = (checkActive) ? poses[i].active : true;
		if (Active)
		{
			// Get Boundaries
			float min_x = poses[i].pos_x - 0.125f;
			float max_x = poses[i].pos_x + 0.125f;
			float min_y = poses[i].pos_y - 0.125f;
			float max_y = poses[i].pos_y + 0.125f;

			// If position is inside of boundary return index of the net
			if (position.x > min_x && position.x < max_x && position.y > min_y && position.y < max_y)
				return i;
		}
	}
	return -1;
}

bool Program::check_game_end()
{
	for (int i = 0; i < sizeof(poses) / sizeof(poses[0]); i++)
	{
		if (poses[i].isEmpty)
			return false;
	}
	// return true when every net is full
	return true;
}