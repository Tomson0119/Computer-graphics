#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"
#include "robot.h"
#include "util.h"

#include <vector>


class Example
{
private:
	Shader* basicShader;
	Shader* textureShader;
	Camera* camera;
	Util* util;

	std::vector<Robot*> robots;
	Robot* player;

	std::vector<Object*> bgs;
	Object* stage;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

	bool isFPV;
	bool move_key[4]; // W A S D
	float player_face;
	float robot_face;

	unsigned int polygon_mode;

public:
	Example(int window_w, int window_h);
	~Example();

	void init();
	void draw();
	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void setTimer();
};