#pragma once

#include <string>

#include <glm/glm.hpp>
#include <gl/glew.h>


class Texture
{
private:
	GLuint texture;

public:
	Texture(const std::string& file);
	~Texture();

	void setTexture(const std::string& file);
	void setActive();
};