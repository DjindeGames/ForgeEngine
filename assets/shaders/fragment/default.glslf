#version 330 core

out vec4 FragColor;
uniform vec4 renderColor;

void main()
{
	FragColor = renderColor;
}