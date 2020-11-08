#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

#include <iostream>

Texture::Texture(const std::string& file)
{
	setTexture(file);
}

Texture::~Texture()
{
}

void Texture::setTexture(const std::string& file)
{
	int channels{ 0 };
	int width, height;

	stbi_set_flip_vertically_on_load(true);
	auto image = stbi_load(file.c_str(), &width, &height, &channels, 0);

	if (!image)
	{
		std::cout << "STB failed to load image " << file << std::endl;
	}

	int format = GL_RGB;
	if (channels == 4)
		format = GL_RGBA;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(image);
}

void Texture::setActive()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
