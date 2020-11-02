#pragma once

#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void setVertexArray() = 0;
	virtual void draw(Shader* shader) = 0;

	glm::mat4 getWorldTransformMat() { return worldTransform; }

	void setWorldMat(const glm::mat4& mat) { worldTransform = mat; }
	void setWorldRotate(const float angle, float x, float y, float z) 
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setWorldTranslate(const glm::vec3& vec)
	{
		worldTransform = glm::translate(worldTransform, vec);
	}
	void setWorldTranslate(float x,float y,float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::translate(worldTransform, vec);
	}	
	void setWorldScale(const glm::vec3& vec)
	{
		worldTransform = glm::scale(worldTransform, vec);
	}
	void setWorldScale(float x,float y,float z)
	{
		glm::vec3 vec(x, y, z);
		worldTransform = glm::scale(worldTransform, vec);
	}

private:
	glm::mat4 worldTransform = glm::mat4(1.0f);
};