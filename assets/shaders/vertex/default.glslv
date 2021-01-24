#version 330 core

//VERTEX SHADER

uniform mat4 Transform;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}