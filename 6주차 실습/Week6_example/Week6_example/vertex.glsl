#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

out vec3 passColor;

uniform mat4 worldTransform;
uniform mat4 viewTransform;

void main()
{
	gl_Position = viewTransform * worldTransform * vec4(inPosition, 1.0);
	passColor = inColor;
}