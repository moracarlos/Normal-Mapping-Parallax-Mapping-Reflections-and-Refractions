#version 330
#extension GL_ARB_separate_shader_objects :enable

#define NUMLIGHTS 3
uniform vec3 diffuseObject, specularObject, ambientObject, sceneAmbient, eyePos;
uniform float roughnessValue, fresnelValue, gaussConstant;
uniform int code;
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

layout(location = 0) out vec4 vFragColor;

void main(void)
{
	if (code==6){
		vFragColor = vec4(0.20, 0.20, 0.20, 1.0);
	}else if (code==7){
		vFragColor = vec4(0.30, 0.30, 0.30, 1.0);
	}else if (code==8){
		vFragColor = vec4(0.40, 0.40, 0.40, 1.0);
	}else if (code==9){
		vFragColor = vec4(0.50, 0.50, 0.50, 1.0);
	}else if (code==10){
		vFragColor = vec4(0.60, 0.60, 0.60, 1.0);
	}else{
		vFragColor = vec4(1,1,1,1);
	}
}