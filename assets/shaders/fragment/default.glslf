#version 330 core

//FRAGMENT SHADER

uniform vec4 RenderColor;
uniform mat4 Transform;

out vec4 FragColor;

void main()
{
	FragColor = RenderColor;
}