#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 world;

void main()
{
	FragPos = vec3(world * vec4(inPos, 1.0f));
	Normal = inNormal;

	gl_Position = vec4(FragPos, 1.0);
}