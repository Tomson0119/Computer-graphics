#pragma once

#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void draw(Shader* shader) = 0;

	glm::mat4 getWorldTransformMat() { return worldTransform; }
	glm::vec3 getPos() { return pos; }

	void setPos(float x, float y, float z) { pos = glm::vec3(x, y, z); }
	void setPos(const glm::vec3& vec) { pos = vec; }

	void setPosRotate(float angle, float x, float y, float z)
	{
		pos = glm::rotate(pos, glm::radians(angle), glm::vec3(x, y, z));
	}
	void setWorldMat(const glm::mat4& mat) { worldTransform = mat; }
	void setWorldMat(float value) { worldTransform = glm::mat4(value); }

	void setWorldRotateBack(const glm::vec3& vec)
	{
		worldTransform = glm::rotate(worldTransform, glm::radians(-rotate), vec);
		rotate = 0.0f;
	}
	void setWorldRotate(const float angle, const glm::vec3& vec)
	{
		rotate += angle;
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setWorldRotate(const float angle, float x, float y, float z)
	{
		rotate += angle;
		glm::vec3 vec(x, y, z);
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setWorldTranslate(const glm::vec3& vec)
	{
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldTranslate(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldScale(const glm::vec3& vec)
	{
		worldTransform = glm::scale(worldTransform, vec);
	}
	void setWorldScale(float value)
	{
		glm::vec3 vec(value);
		worldTransform = glm::scale(worldTransform, vec);
	}
	void setWorldScale(float x, float y, float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::scale(worldTransform, vec);
	}

	void rotateOrigin(float angle, float x, float y, float z)
	{
		glm::vec3 temp = pos;
		pos -= pos;
		setPosRotate(angle, x, y, z);
		pos += temp;
	}

	void translateToPos()
	{
		setWorldTranslate(pos);
	}


private:
	glm::mat4 worldTransform = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	float rotate = 0.0f;
};