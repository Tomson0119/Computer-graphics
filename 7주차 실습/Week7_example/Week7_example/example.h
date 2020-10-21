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
	std::vector<Object*> crane;

	float angle;
	float rotate;

	// For Scene 1
	float orbit;
	float small_orbit;

	// For Scene 2
	float up_angle;
	float up_rotate;
	float front_angle;	
	float front_rotate;

	//For Scene 3
	float bottom_angle;
	float bottom_rotate;
	float mid_angle;
	float mid_rotate;
	float top_angle;
	float top_rotate;
	float move;
	float move_x;

	const float rotate_speed = 1.5f;
	const float move_dist = 0.03f;

	unsigned int draw_mode; // For Scene 2
	unsigned int polygon_mode;
	unsigned int project_mode; // For Scene 2
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
	void sceneThree_init();

	void sceneOne_draw();
	void sceneTwo_draw();
	void sceneThree_draw();

	void sceneOne_key_event(unsigned char key, int x, int y);
	void sceneTwo_key_event(unsigned char key, int x, int y);
	void sceneThree_key_event(unsigned char key, int x, int y);

private:
	struct Camera
	{
		glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Position = glm::vec3(0.0f, 0.2f, 4.0f);
	};

	Camera camera = Camera();

	glm::mat4 viewMat;
	glm::mat4 projMat;
};