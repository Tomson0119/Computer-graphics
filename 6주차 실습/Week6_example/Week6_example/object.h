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


	glm::mat4 getTransformMat() { return transformMat; }


	void setMat(const glm::mat4& mat) { transformMat = mat; }
	void setMatRotate(const float angle, const glm::vec3& vec) 
	{
		transformMat = glm::rotate(transformMat, glm::radians(angle), vec); 
	}
	void setMatTranslate(const glm::vec3& vec)
	{
		transformMat = glm::translate(transformMat, vec);
	}

private:
	glm::mat4 transformMat = glm::mat4(1.0f);

};