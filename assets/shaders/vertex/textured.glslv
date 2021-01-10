#version 330 core

//VERTEX SHADER

uniform mat4 Transform;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPos;
//ATTRIBUTE 2
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * Transform;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}