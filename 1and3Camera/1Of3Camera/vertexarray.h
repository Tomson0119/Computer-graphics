#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <gl/glew.h>


class VertexArray
{
private:
	GLuint VAO;
	GLuint VBO[3];
	GLuint IBO;

public:
	VertexArray(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals,
		const std::vector<glm::vec2>& texCoord,
		const std::vector<unsigned int>& indices);

	VertexArray(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals,
		const std::vector<unsigned int>& indices);

	VertexArray(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals);

	~VertexArray();

	void setActive();

private:
	void set_buffer(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals,
		const std::vector<glm::vec2>& texCoord,
		const std::vector<unsigned int>& indices);

	void set_buffer(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals,
		const std::vector<unsigned int>& indices);

	void set_buffer(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals);
};