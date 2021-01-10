#version 330 core

//FRAGMENT SHADER

uniform sampler2D RenderTexture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(RenderTexture, TexCoord);
}