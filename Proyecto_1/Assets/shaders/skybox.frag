#version 330
#extension GL_ARB_separate_shader_objects :enable

#define NUMLIGHTS 2
uniform sampler2D textureSampler;
uniform sampler2D normalSampler; //heightMap
uniform vec3 diffuseObject, specularObject, ambientObject, sceneAmbient, eyePos;
uniform float roughnessValue, fresnelValue, gaussConstant;

uniform struct	LightParameters{
	int type;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	float shininness;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	vec3 spotDirection;
	float spotExponent;
	float spotCutoff;
	float spotCosCutoff;
}lightParameters[NUMLIGHTS];

in vec3 vVertexColor;
in vec3 fPosition;
in vec3 fNormal;
in vec2 UV;
in vec3 fTangent;
in vec3 fBitangent;
in vec3 eyeVec; 

layout(location = 0) out vec4 vFragColor;

void main(void)
{
	vFragColor = vec4(vec3(texture(textureSampler, UV.xy)), 1.0);
}

