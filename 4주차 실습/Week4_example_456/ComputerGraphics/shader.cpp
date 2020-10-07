#include "shader.h"

Shader::Shader() {
	program = NULL;
	VAO = NULL;
	VBO[0] = NULL;
	VBO[1] = NULL;
}

void Shader::make_vertex(const GLchar *vertexPath, GLuint &vertex)
{
	std::string vertexCode;

	try
	{
		std::ifstream vShaderFile;
		std::stringstream vShaderStream;

		vShaderFile.open(vertexPath);
		vShaderStream << vShaderFile.rdbuf();

		vShaderFile.close();

		vertexCode = vShaderStream.str();		
	}
	catch (std::ifstream::failure e)
	{
		std::cout << " Shader code path error" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();

	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Vertex Shader Error\n" << infoLog << std::endl;
	}
}

void Shader::make_fragment(const GLchar* fragmentPath, GLuint &fragment)
{
	std::string fragmentCode;

	try
	{
		std::ifstream fShaderFile;
		std::stringstream fShaderStream;

		fShaderFile.open(fragmentPath);
		fShaderStream << fShaderFile.rdbuf();

		fShaderFile.close();

		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader code path error" << std::endl;
	}

	const GLchar* fShaderCode = fragmentCode.c_str();

	GLint success;
	GLchar infoLog[512];

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "fragment Shader Error\n" << infoLog << std::endl;
	}
}

GLvoid Shader::make_shader(const GLchar *vertexPath, const GLchar* fragmentPath)
{
	GLuint vertex, fragment;

	make_vertex(vertexPath, vertex);
	make_fragment(fragmentPath, fragment);

	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Link error\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

GLvoid Shader::init_buffer(float(*vertexPosition)[3], float(*vertexColor)[3], int row)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, row * 3 * sizeof(GLfloat), vertexPosition, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, row * 3 * sizeof(GLfloat), vertexColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

GLvoid Shader::reset_buffer(float(*vertexPosition)[3], float(*vertexColor)[3], int row)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, row * 3 * sizeof(GLfloat), vertexPosition, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, row * 3 * sizeof(GLfloat), vertexColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Shader::use_program()
{
	glUseProgram(program);
}

GLuint Shader::getProgram()
{
	return program;
}

