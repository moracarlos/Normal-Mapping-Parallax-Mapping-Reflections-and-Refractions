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
	float NdotL, distance, NdotRV, att, spotEffect;
	vec3 ambient, diffuse, specular, globalAmbient;
	vec3 lightDir;
	vec3 finalLight = sceneAmbient * ambientObject;
	for (int i=0; i<NUMLIGHTS; i++)
	{
		if (lightParameters[i].type == 1){
			lightDir = -lightParameters[i].spotDirection;
			NdotL = max(dot(fNormal, lightDir), 0.0);
			diffuse = diffuseObject * lightParameters[i].diffuse;
			ambient = ambientObject * lightParameters[i].ambient;
			if (NdotL>0.0){
				finalLight+= NdotL * diffuse+ambient;
				vec3 R = reflect(-lightDir, fNormal);
				vec3 V = normalize(eyePos-fPosition);
				NdotRV = max(dot(R,V), 0.0);
				specular = specularObject * lightParameters[i].specular * pow(NdotRV, lightParameters[i].shininness);
				finalLight += specular;
			}
		}
	}

	//Parallax
	float scale = 0.04, bias = 0.02;

	float height = texture2D(normalSampler, UV.xy).r;
	float v = height * scale - bias;
	vec3 eye = normalize(eyeVec);
	vec2 newCoords = UV + (eye.xy * v);
	vec3 rgb = texture2D(textureSampler, newCoords).rgb;
	
	vec4 ilumination = vec4(clamp(finalLight, vec3(0), vec3(1)), 1.0);
	vFragColor = clamp(vec4(rgb, 1.0)*ilumination, vec4(0), vec4(1));

	//vFragColor = vec4(rgb, 1.0);
}

