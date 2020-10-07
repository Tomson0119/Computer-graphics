#pragma once

#include "util.h"

class Shader
{
private:
	GLuint program;	
	GLuint VAO, VBO[2];

	void make_vertex(const GLchar* vertexPath, GLuint &vertex);
	void make_fragment(const GLchar* fragmentPath, GLuint &fragment);
	
public:
	Shader();

	GLvoid init_buffer(float(*vertexPosition)[3], float(*vertexColor)[3], int row);

	GLvoid reset_buffer(float(*vertexPosition)[3], float(*vertexColor)[3], int row);
	GLvoid make_shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use_program();

	GLuint getProgram();
};