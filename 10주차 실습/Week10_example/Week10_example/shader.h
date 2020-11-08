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

public:
	Shader();
	~Shader();

	bool make_shader(const std::string& vPath, const std::string& fPath);

	void setMat4(const std::string& name, const glm::mat4& mat);
	void setVec3(const std::string& name, const glm::vec3& vec);
	void setInt(const std::string& name, int value);

	void use_program();

private:
	std::string getCode(const std::string& path);

	bool compileShader(const std::string& fileName, GLuint shaderType, GLuint& outShader);
	bool isCompiled(GLuint shader, const std::string& name);
	bool isValidProgram();
};