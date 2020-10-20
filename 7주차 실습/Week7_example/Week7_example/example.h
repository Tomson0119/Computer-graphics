#pragma once

#include <vector>

#include "shader.h"
#include "object.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


class Example
{
private:
	Shader* shader;
	std::vector<Object*> objs;

	float angle;
	float rotate;

	float orbit;
	float small_orbit;

	// For Example Scene 2
	float up_angle;
	float up_rotate;
	float front_angle;	
	float front_rotate;

	const float rotate_speed = 1.5f;
	const float move_dist = 0.08f;

	unsigned int draw_mode;
	unsigned int polygon_mode;
	unsigned int project_mode;
	unsigned int example_scene;

	unsigned int window_w;
	unsigned int window_h;

public:
	Example();
	~Example();

	void init(int window_w, int window_h);

	void draw();
	void key_event(unsigned char key, int x, int y);
	bool setTimer();

private:
	void sceneOne_init();
	void sceneTwo_init();

	void sceneOne_draw();
	void sceneTwo_draw();

	void sceneOne_key_event(unsigned char key, int x, int y);
	void sceneTwo_key_event(unsigned char key, int x, int y);

private:
	struct Camera
	{
		const glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);
		const glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		const glm::vec3 Position = glm::vec3(0.0f, 0.2f, 4.0f);
	};

	const Camera camera = Camera();

	glm::mat4 viewMat;
	glm::mat4 projMat;
};