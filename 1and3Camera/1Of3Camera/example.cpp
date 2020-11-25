#include "example.h"
#include "rectangle.h"
#include "cube.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Example::Example(int window_w, int window_h)
{
	basicShader = new Shader();
	textureShader = new Shader();

	camera = new Camera(window_w, window_h);
	util = new Util();

	lightPos = vec3(0.0f, 1.0f, 8.0f);
	lightColor = vec3(1.0f);

	stage = nullptr;
	player = nullptr;

	isFPV = false;

	for (int i = 0; i < 4; i++)
		move_key[i] = false;

	player_face = 0.0f;
	robot_face = 0.0f;
	polygon_mode = GL_FILL;
}

Example::~Example()
{
	for (auto bg : bgs)
		delete bg;
	std::vector<Object*>().swap(bgs);

	for (auto robot : robots)
		delete robot;
	std::vector<Robot*>().swap(robots);

	delete textureShader;
	delete basicShader;
	delete camera;
	delete util;
}

void Example::init()
{
	basicShader->make_shader("basic.vs", "basic.fs");
	textureShader->make_shader("texture.vs", "texture.fs");

	camera->translateCameraPos(0.0f, 1.0f, 0.5f);

	// Initialize Background
	for (int i = 0; i < 4; i++) {
		bgs.push_back(new Rect("sky.png"));	

		float angle = 0.0f;
		if (i == 1) angle = 90.0f;
		else if (i == 2) angle = -90.0f;
		else if (i == 3) angle = 180.0f;
		bgs.at(i)->setWorldRotate(angle, 0.0f, 1.0f, 0.0f);
		bgs.at(i)->setWorldTranslate(0.0f, 0.0f, -5.0f);
		bgs.at(i)->setWorldScale(15.0f, 15.0f, 1.0f);
	}	

	// Initialize Stage
	stage = new Rect("wall.png");
	stage->setWorldRotate(-90.0f, 1.0f, 0.0f, 0.0f);
	stage->setWorldScale(5.0f, 5.0f, 1.0f);
	stage->setWorldTranslate(0.0f, 0.0f, -0.5f);

	// Set player
	player = new Robot();
	player->setPlayer();

	// Random robots
	int number = 4;
	for (int i = 0; i < number; i++)
	{
		robots.push_back(new Robot());
		glm::vec3 pos = glm::vec3(util->generateFloat(-1.0f, 1.0f), 0.0f, util->generateFloat(-1.0f, 1.0f));
		robots.at(robots.size() - 1)->setFirstPos(pos);
		robots.at(robots.size() - 1)->translateWorld(pos);
	}
}

void Example::draw()
{
	// Basic
	basicShader->use_program();
	basicShader->setMat4("view", camera->getViewMat());
	basicShader->setMat4("proj", camera->getProjMat());
	player->draw(basicShader);
	for (unsigned int i = 0; i < robots.size(); i++)
		robots.at(i)->draw(basicShader);	

	// Texture
	textureShader->use_program();
	textureShader->setMat4("view", camera->getViewMat());
	textureShader->setMat4("proj", camera->getProjMat());
	textureShader->setVec3("lightColor", lightColor);
	textureShader->setVec3("lightPos", lightPos);
	textureShader->setVec3("viewPos", camera->getPosition());
	textureShader->setVec3("objectColor", vec3(1.0f));
	for (unsigned int i = 0; i < bgs.size(); i++)
		bgs.at(i)->draw(textureShader);
	stage->draw(textureShader);
}

void Example::keyDown(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q') {
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}
	if (key == 'm' || key == 'M') {
		polygon_mode = (polygon_mode == GL_FILL) ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
	}
	if (key == 'c' || key == 'C') {
		stage->setWorldRotate(1.0f, 0.0f, 0.0f, 1.0f);
		player->rotateAroundCenter(1.0f);
		for (unsigned int i = 0; i < robots.size(); i++)
			robots.at(i)->rotateAroundCenter(1.0f);
	}
	if (key == 'v' || key == 'V') {
		stage->setWorldRotate(-1.0f, 0.0f, 0.0f, 1.0f);
		player->rotateAroundCenter(-1.0f);
		for (unsigned int i = 0; i < robots.size(); i++)
			robots.at(i)->rotateAroundCenter(-1.0f);
	}
	if (key == 'y' || key == 'Y') {
		camera->rotateCameraCenter(1.5f, 0.0f, 1.0f, 0.0f);
	}
	if (key == 'g' || key == 'G')
	{
		stage->setWorldRotateBack(glm::vec3(0.0f, 0.0f, 1.0f));
		player_face = 0.0f;
		player->reset();
		for (unsigned int i = 0; i < robots.size(); i++)
			robots.at(i)->reset();
		isFPV = false;
		camera->thirdPointView();
	}

	// Change View
	if (key == 49) {
		isFPV = true;
		camera->firstPointView(player->getPos(), player_face);
	}
	if (key == 51) {
		isFPV = false;
		camera->thirdPointView();
	}

	// Move Key
	if (key == 'w' || key == 'W')
		move_key[0] = true;
	if (key == 'a' || key == 'A') 
		move_key[1] = true;
	if (key == 's' || key == 'S')
		move_key[2] = true;
	if (key == 'd' || key == 'D')
		move_key[3] = true;
}

void Example::keyUp(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
		move_key[0] = false;
	if (key == 'a' || key == 'A')
		move_key[1] = false;
	if (key == 's' || key == 'S')
		move_key[2] = false;
	if (key == 'd' || key == 'D')
		move_key[3] = false;
} 

void Example::setTimer()
{
	// Move
	float move_speed = 0.01f;
	glm::vec3 curr_pos = player->getPos();
	if (move_key[0]) // W
	{
		player_face = (move_key[1]) ? -135.0f : ((move_key[3]) ? 135.0f : 180.0f);
		if(curr_pos.z > -1.8f) player->translateWorld(0.0f, 0.0f, -move_speed);
	}
	if (move_key[1]) // A
	{
		if(!move_key[0]) player_face = (move_key[2]) ? -45.0f : -90.0f;
		if(curr_pos.x > -1.8f) player->translateWorld(-move_speed, 0.0f, 0.0f);
	}
	if (move_key[2]) // S
	{
		if(!move_key[1]) player_face = (move_key[3]) ? 45.0f : 0.0f;
		if(curr_pos.z < 1.8f) player->translateWorld(0.0f, 0.0f, move_speed);
	}
	if (move_key[3]) // D
	{
		if(!move_key[0] && !move_key[2]) player_face = 90.0f;
		if(curr_pos.x < 1.8f) player->translateWorld(move_speed, 0.0f, 0.0f);
	}
	if (isFPV) camera->firstPointView(curr_pos, player_face);
	player->rotateDirection(player_face);

	// Animation
	player->setTimer();
	for (unsigned int i = 0; i < robots.size(); i++)
		robots.at(i)->setTimer();

	
	// Robot Follow
	for (unsigned int i = 0; i < robots.size(); i++)
	{
		// get each position of robot and player
		glm::vec3 playerPos = player->getPos();
		glm::vec3 robotPos = robots.at(i)->getPos();

		glm::vec2 p1 = glm::vec2(playerPos.x, playerPos.z);
		glm::vec2 p2 = glm::vec2(robotPos.x, robotPos.z);

		// get distance between two position
		if (util->getDistance(p1, p2) < 0.6f)
		{			
			// robot follows to position behind of player
			glm::vec3 posBehind = player->getBehindPos();
			glm::vec2 target = glm::vec2(posBehind.x, posBehind.z);

			// Get angle towards player and implement it
			robot_face = util->getAngle(p2, p1);
			robots.at(i)->rotateDirection(robot_face);
			robots.at(i)->translateAlong(target, 0.01f);
		}
	}	
}
