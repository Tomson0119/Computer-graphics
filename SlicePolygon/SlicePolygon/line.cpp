#include "line.h"


Line::Line(const glm::vec2& vec)
{
	worldTransform = glm::mat4(1.0f);
	
	vertices.emplace_back(glm::vec3(vec, 0.0f));
	vertices.emplace_back(glm::vec3(vec, 0.0f));

	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices.emplace_back(0);
	indices.emplace_back(1);

	setVertexArray();
}

Line::Line(const glm::vec2& begin, const glm::vec2& end)
{
	worldTransform = glm::mat4(1.0f);

	vertices.emplace_back(glm::vec3(begin, 0.0f));
	vertices.emplace_back(glm::vec3(end, 0.0f));

	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices.emplace_back(0);
	indices.emplace_back(1);

	setVertexArray();
}

Line::Line(float x1, float y1, float x2, float y2)
{
	worldTransform = glm::mat4(1.0f);

	vertices.emplace_back(glm::vec3(x1, y1, 0.0f));
	vertices.emplace_back(glm::vec3(x2, y2, 0.0f));

	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices.emplace_back(0);
	indices.emplace_back(1);

	setVertexArray();
}

Line::~Line()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}

void Line::changePos(const glm::vec2& pos)
{
	// changed last vertex and update vertex array
	vertices.at(1) = glm::vec3(pos, 0.0f);
	setVertexArray();
}

void Line::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals, indices);
}

void Line::draw(Shader* shader)
{
	shader->setMat4("world", worldTransform);
	vertexArray->setActive();
	glDrawElements(GL_LINE_LOOP, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
