#include "shader.h"

Shader::Shader()
{
	program = NULL;
	VAO = NULL;
	VBO[0] = NULL;
	VBO[1] = NULL;
}

void Shader::make_shader(const GLchar* vPath, const GLchar* fPath)
{
	std::string vCode = getCode(vPath).c_str();
	std::string fCode = getCode(fPath).c_str();

	const GLchar* vertexCode = vCode.c_str();
	const GLchar* fragCode = fCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Vertex Shader Error\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Fragment Shader Error\n" << infoLog << std::endl;
	}

	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program Link Error\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::init_buffer(float* vPos, float* vColor, int size)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

	reset_buffer(vPos, vColor, size);
}

void Shader::reset_buffer(float* vPos, float* vColor, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
}

void Shader::use_program()
{
	glUseProgram(program);
}

std::string Shader::getCode(const GLchar* path)
{
	std::string code;
	try
	{
		std::ifstream file;
		std::stringstream stream;

		file.open(path);
		stream << file.rdbuf();

		file.close();

		code = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader code path error" << std::endl;
	}
	return code;
}