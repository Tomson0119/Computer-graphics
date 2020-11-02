#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>


class Example
{
private:
	Shader* lightShader;
	Shader* lampShader; 
	Camera* camera;

	std::vector<Object*> objs;
	Object* light_bulb;

	glm::vec3 lightPos;

	unsigned int polygon_mode;

public:
	Example(int window_w, int window_h);
	~Example();

	void init();
	void draw();
	void key_event(unsigned char key, int x, int y);
	void setTimer();
};