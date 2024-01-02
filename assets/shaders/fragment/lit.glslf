#version 330 core

//FRAGMENT SHADER

uniform float AmbientLightIntensity;
uniform vec4 RenderColor;
uniform vec4 LightColor;
uniform vec4 LightSourcePosition;
uniform sampler2D RenderTexture;

in vec3 ourNormal;
in vec4 ourFragmentPosition;
in vec2 ourTextureCoordinates;

out vec4 FragColor;

void main()
{
	vec3 lightDirection = vec3(normalize(LightSourcePosition - ourFragmentPosition));
	float diffuseFactor = max(dot(lightDirection, ourNormal), 0.0);
	vec4 diffuseLight = diffuseFactor * LightColor;
	vec4 result = texture(RenderTexture, ourTextureCoordinates) * RenderColor * (min(diffuseLight + AmbientLightIntensity, 1.0));
	FragColor = vec4(result.x, result.y, result.z, RenderColor.w);
}