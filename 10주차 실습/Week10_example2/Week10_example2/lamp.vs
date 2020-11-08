#version 330 core
layout(location = 0) in vec3 inPos;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * world * vec4(inPos, 1.0f);
}