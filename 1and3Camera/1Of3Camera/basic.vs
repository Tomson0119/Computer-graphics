#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

out vec3 FragPos;

uniform mat4 world;
uniform mat4 outWorld;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	FragPos = vec3(outWorld * world * vec4(inPos, 1.0f));
	gl_Position = proj * view * vec4(FragPos, 1.0);
}