#version 330 core

//FRAGMENT SHADER

uniform vec4 renderColor;
uniform sampler2D renderTexture;

out vec4 FragColor;
in vec2 TexCoord;

void main()
{
	FragColor = texture(renderTexture, TexCoord);
}