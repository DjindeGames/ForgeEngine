#version 330 core

//FRAGMENT SHADER

uniform float AmbientLightIntensity;
uniform vec4 RenderColor;
uniform vec4 LightColor;
uniform vec4 LightSourcePosition;
uniform vec4 CameraPosition;
uniform float LightRange;
uniform sampler2D RenderTexture;
uniform int Shininess;
uniform float SpecularIntensity;

in vec3 ourNormal;
in vec4 ourFragmentPosition;
in vec2 ourTextureCoordinates;

out vec4 FragColor;

void main()
{
    vec3 directionToLight = vec3(LightSourcePosition - ourFragmentPosition);
	float distanceToLight = length(directionToLight);
	float distanceRatio = distanceToLight / LightRange;
	vec3 directionToLightNormalized = normalize(directionToLight);
	vec3 eyeDirection = vec3(normalize(CameraPosition - ourFragmentPosition));
	vec3 lightRayReflection = reflect(-directionToLightNormalized, ourNormal);
	
	float specularFactor = pow(max(dot(eyeDirection, lightRayReflection), 0), Shininess);
	vec4 specularLight = SpecularIntensity * specularFactor * LightColor;
	float diffuseFactor = max(dot(directionToLightNormalized, ourNormal), 0.0);
	vec4 diffuseLight = diffuseFactor * LightColor * (1 - distanceRatio);

	vec4 result = texture(RenderTexture, ourTextureCoordinates) * RenderColor * (min(diffuseLight + specularLight + AmbientLightIntensity, 1.0));
	FragColor = vec4(result.x, result.y, result.z, RenderColor.w);
}