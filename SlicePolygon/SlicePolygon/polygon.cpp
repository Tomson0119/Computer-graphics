#include "polygon.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Poly::Poly()
{
	glm::vec2 tri[4][3] = {
		{ glm::vec2(0.0f,  0.15f), glm::vec2(-0.15f, -0.15f), glm::vec2(0.15f, -0.15f) },
		{ glm::vec2(-0.2f,  0.05f), glm::vec2(0.10f, -0.15f), glm::vec2(0.10f,  0.13f) }, 
		{ glm::vec2(-0.1f,  0.10f), glm::vec2(-0.13f, -0.20f), glm::vec2(0.14f, 0.00f) },
		{ glm::vec2(0.21f, 0.13f), glm::vec2(-0.13f, -0.10f), glm::vec2(0.13f, -0.10f) }
	};

	glm::vec2 rect[4][4] = {
		{ glm::vec2(-0.15f, 0.15f), glm::vec2(-0.16f, -0.15f), glm::vec2(0.14f, -0.14f), glm::vec2(0.15f, 0.16f) },
		{ glm::vec2(-0.12f, 0.13f), glm::vec2(-0.15f, -0.15f), glm::vec2(0.18f, -0.15f), glm::vec2(0.11f, 0.13f) },
		{ glm::vec2(-0.15f, 0.10f), glm::vec2(-0.13f, -0.15f), glm::vec2(0.23f, -0.10f), glm::vec2(0.10f, 0.20f) },
		{ glm::vec2(-0.20f, 0.00f), glm::vec2(-0.05f, -0.19f), glm::vec2(0.22f,  0.00f), glm::vec2(-0.05f, 0.17f) }
	};

	{
		int rectangle = rand() % 2;
		int index = rand() % 4;
		std::cout << index << "th polygon created .." << std::endl;
		if (rectangle) {
			vertices.emplace_back(glm::vec3(rect[index][0], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][1], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][2], 0.0f));
			vertices.emplace_back(glm::vec3(rect[index][3], 0.0f));
		}
		else {
			vertices.emplace_back(glm::vec3(tri[index][0], 0.0f));
			vertices.emplace_back(glm::vec3(tri[index][1], 0.0f));
			vertices.emplace_back(glm::vec3(tri[index][2], 0.0f));
		}

		for (unsigned int i = 0; i < vertices.size(); i++)
			normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < vertices.size() - 2; i++)
		{
			indices.emplace_back(0);
			indices.emplace_back(i + 1);
			indices.emplace_back(i + 2);
		}
	}

	worldTransform = glm::mat4(1.0f);
	pos = glm::vec2(0.0f);
	setVertexArray();
}

Poly::Poly(const std::vector<glm::vec2>& container)
{	
	for (unsigned int i = 0; i < container.size(); i++)
		vertices.push_back(glm::vec3(container.at(i), 0.0f));

	for (unsigned int i = 0; i < vertices.size(); i++)
		normals.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

	for (int i = 0; i < vertices.size() - 2; i++)
	{
		indices.emplace_back(0);
		indices.emplace_back(i+1);
		indices.emplace_back(i+2);
	}
	worldTransform = glm::mat4(1.0f);
	pos = glm::vec2(0.0f);
	setVertexArray();
}

Poly::~Poly()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(normals);
	std::vector<unsigned int>().swap(indices);
	delete vertexArray;
}

glm::vec2 Poly::getVertex2(int index)
{
	if (index >= vertices.size())
		return glm::vec2(-100.0f);
	return glm::vec2(vertices.at(index).x, vertices.at(index).y);
}

void Poly::translateAlong(const glm::vec2& target, float speed)
{
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;

	float distance = sqrt(pow(dx, 2) + pow(dy, 2));

	if (distance == 0) return;

	float x = dx / distance * speed;
	float y = dy / distance * speed;

	translateWorld(x, y);
}

void Poly::translateWorld(float x, float y)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
		vertices.at(i) += glm::vec3(x, y, 0.0f);
	pos += glm::vec2(x, y);
	worldTransform = glm::translate(worldTransform, glm::vec3(x, y, 0.0f));
}

void Poly::setVertexArray()
{
	vertexArray = new VertexArray(vertices, normals, indices);
}

void Poly::draw(Shader* shader)
{
	shader->setMat4("world", worldTransform);
	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
