#version 330 core

in vec3 passColor;
out vec4 frag_color;

void main()
{
	frag_color = vec4(passColor,1.0);
}