#pragma once

#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

class Shader
{
private:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	
	GLint worldLocation;
	GLint viewLocation;
public:
	Shader();
	~Shader();

	bool make_shader(const std::string& vPath, const std::string& fPath);
	
	void setWorldTransform(const glm::mat4& mat);
	void setViewTransform(const glm::mat4& mat);
	void use_program();

private:
	std::string getCode(const std::string& path);

	bool compileShader(const std::string& fileName, GLuint shaderType, GLuint& outShader);
	bool isCompiled(GLuint shader, const std::string& name);
	bool isValidProgram();
};