#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>


Shader::Shader()
{
	program = NULL;
	vertexShader = NULL;
	fragmentShader = NULL;
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

bool Shader::make_shader(const std::string& vPath, const std::string& fPath)
{
	if (!compileShader(vPath, GL_VERTEX_SHADER, vertexShader) ||
		!compileShader(fPath, GL_FRAGMENT_SHADER, fragmentShader))
	{
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (!isValidProgram())
	{
		return false;
	}
	return true;	
}

void Shader::setMatTransform(const std::string& name, const glm::mat4& mat)
{
	GLuint location = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::use_program()
{
	glUseProgram(program);
}

std::string Shader::getCode(const std::string& path)
{
	std::string code;
	std::ifstream file;
	std::stringstream stream;

	file.open(path);

	if (!file.is_open())
	{
		std::cout << "Shader code path error\n"<< path << std::endl;
		return "";
	}

	stream << file.rdbuf();
	code = stream.str();
	
	return code;
}

bool Shader::compileShader(const std::string& fileName, 
	GLuint shaderType, GLuint& outShader)
{
	std::string str_code = getCode(fileName);
	if (str_code == "")
	{
		return false;
	}
	
	const char* code = str_code.c_str();

	outShader = glCreateShader(shaderType);
	glShaderSource(outShader, 1, &code, NULL);
	glCompileShader(outShader);

	return isCompiled(outShader, fileName);
}

bool Shader::isCompiled(GLuint shader, const std::string& name)
{
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << name << " compile error\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Shader::isValidProgram()
{
	GLint success;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program Link Error\n" << infoLog << std::endl;
		return false;
	}
	return true;
}