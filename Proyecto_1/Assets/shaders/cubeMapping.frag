#version 330
#extension GL_ARB_separate_shader_objects :enable

#define NUMLIGHTS 2
uniform samplerCube cubemapSampler;
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


layout(location = 0) out vec4 vFragColor;

void main(void)
{
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(eyePos-fPosition);
	vec3 R = refract(I,normalize(fNormal), ratio);
	vFragColor = texture(cubemapSampler, R);
}

