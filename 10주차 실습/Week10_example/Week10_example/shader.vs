#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	FragPos = vec3(world * vec4(inPos, 1.0f));
	Normal = inNormal;
	TexCoord = inTexCoord;

	gl_Position = proj * view * vec4(FragPos, 1.0);
}