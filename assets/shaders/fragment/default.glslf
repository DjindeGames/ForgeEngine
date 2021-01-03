#version 330 core

//FRAGMENT SHADER

out vec4 FragColor;
uniform vec4 renderColor;

void main()
{
	FragColor = renderColor;
}