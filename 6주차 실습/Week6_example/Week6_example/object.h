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

	glm::mat4 getViewTransformMat() { return viewTransform; }
	glm::mat4 getWorldTransformMat() { return worldTransform; }


	void setViewMat(const glm::mat4& mat) { viewTransform = mat; }
	void setWorldMat(const glm::mat4& mat) { worldTransform = mat; }

	void setMatRotate(const float angle, const glm::vec3& vec) 
	{
		worldTransform = glm::rotate(worldTransform, glm::radians(angle), vec);
	}
	void setMatTranslate(const glm::vec3& vec)
	{
		worldTransform = glm::translate(worldTransform, vec);
	}

private:
	glm::mat4 viewTransform = glm::mat4(1.0f);
	glm::mat4 worldTransform = glm::mat4(1.0f);
};