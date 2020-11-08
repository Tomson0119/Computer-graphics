#version 330 core

out vec4 outColor;

in vec3 FragPos;
in vec4 FragColor;

void main()
{
	outColor = FragColor;
}