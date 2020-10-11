#pragma once

#include "util.h"

class Shader
{
private:
	GLuint program;
	GLuint VAO, VBO[2];

	std::string getCode(const GLchar* path);
public:
	Shader();

	void make_shader(const GLchar* vPath, const GLchar* fPath);
	void init_buffer(float* vPos, float* vColor, int size);
	void reset_buffer(float* vPos, float* vColor, int size);
	void use_program();
};