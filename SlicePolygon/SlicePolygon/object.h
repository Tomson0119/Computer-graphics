#pragma once

#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void setVertexArray() = 0;
	virtual void draw(Shader* shader) = 0;

	glm::mat4 getWorldTransformMat() { return worldTransform; }
	glm::vec3 getPos() { return pos; }

	void setWorldMat(const glm::mat4& mat) { worldTransform = mat; }

	void setWorldRotate(const float angle, const glm::vec3& vec)
	{
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setWorldRotate(const float angle, float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setWorldTranslate(const glm::vec3& vec)
	{
		pos += vec;
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldTranslate(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		pos += vec;
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldScale(const glm::vec3& vec)
	{
		worldTransform = glm::scale(worldTransform, vec);
	}
	void setWorldScale(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::scale(worldTransform, vec);
	}

	void translateAlong(const glm::vec2& target, float speed)
	{
		float dx = target.x - pos.x;
		float dy = target.y - pos.y;

		float distance = sqrt(pow(dx, 2) + pow(dy, 2));

		if (distance == 0) return;

		float x = dx / distance * speed;
		float y = dy / distance * speed;

		setWorldTranslate(x, y, 0.0f);
	}

private:
	glm::mat4 worldTransform = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(0.0f);
};