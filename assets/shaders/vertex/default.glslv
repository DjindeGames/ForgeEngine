#version 330 core

//VERTEX SHADER

//ATTRIBUTE 1
layout (location = 0) in vec3 aPos;
//ATTRIBUTE 2
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}