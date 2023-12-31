#version 330 core

//FRAGMENT SHADER

uniform vec4 RenderColor;
uniform vec4 LightColor;
uniform vec4 LightSourcePosition;

in vec3 ourNormal;
in vec4 ourFragmentPosition;

out vec4 FragColor;

void main()
{
	vec3 lightDirection = vec3(normalize(LightSourcePosition - ourFragmentPosition));
	float diffuseFactor = max(dot(lightDirection, ourNormal), 0.0);
	vec4 diffuseLight = diffuseFactor * LightColor;
	//FragColor = RenderColor * diffuseLight;
	FragColor = RenderColor;
}