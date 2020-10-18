#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <gl/glew.h>


class VertexArray
{
private:
	GLuint VAO;
	GLuint VBO[2];
	GLuint IBO;

public:
	VertexArray(const std::vector<glm::vec3>& vertices,
				const std::vector<glm::vec3>& colors,
				const std::vector<unsigned int>& indices);

	~VertexArray();

	void setActive();

private:
	void set_buffer(const std::vector<glm::vec3>& vertices,
					const std::vector<glm::vec3>& colors,
					const std::vector<unsigned int>& indices);
};