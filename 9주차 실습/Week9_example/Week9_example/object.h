#pragma once

#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
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
		pos = pos + vec * scale;
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldTranslate(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		pos = pos + vec * scale;
		worldTransform = glm::translate(worldTransform, vec);
		std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
	void setWorldScale(const glm::vec3& vec)
	{
		scale = vec * scale;
		worldTransform = glm::scale(worldTransform, vec);
	}
	void setWorldScale(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		scale = vec * scale;
		worldTransform = glm::scale(worldTransform, vec);
	}

	void rotateOrigin(float angle, float x, float y, float z)
	{
		worldTransform = glm::translate(worldTransform, -pos);
		setWorldRotate(angle, glm::vec3(x,y,z));
		worldTransform = glm::translate(worldTransform, pos);
	}


private:
	glm::mat4 worldTransform = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
};