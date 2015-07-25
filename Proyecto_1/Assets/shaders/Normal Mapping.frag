#version 330
#extension GL_ARB_separate_shader_objects :enable

#define NUMLIGHTS 2
uniform sampler2D textureSampler;
uniform sampler2D normalSampler;
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
	float NdotL, distance, NdotRV, att, spotEffect;
	vec3 ambient, diffuse, specular, globalAmbient;
	vec3 lightDir;
	vec3 finalLight = sceneAmbient * ambientObject;
	for (int i=0; i<NUMLIGHTS; i++)
	{
		if (lightParameters[i].type == 1){
			lightDir = normalize(lightParameters[i].position-fPosition);
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
		else if (lightParameters[i].type == 2){ //Puntual
			lightDir = lightParameters[i].position-fPosition;
			distance = length(lightDir);
			NdotL = max(dot(fNormal, normalize(lightDir)), 0.0);
			diffuse = diffuseObject * lightParameters[i].diffuse;
			ambient = ambientObject * lightParameters[i].ambient;
			if (NdotL>0.0){
				att = 1.0/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);
				finalLight+= att*(NdotL * diffuse + ambient);
				float NdotRV;
				vec3 R = reflect(-normalize(lightDir), fNormal);
				vec3 V = normalize(eyePos-fPosition);
				NdotRV = max(dot(R,V), 0.0);
				specular = specularObject * lightParameters[i].specular * pow(NdotRV, lightParameters[i].shininness);
				finalLight += att*(specular);
			}
		}
		else if (lightParameters[i].type == 3){
			lightDir = lightParameters[i].position-fPosition;
			distance = length(lightDir);
			NdotL = max(dot(fNormal, normalize(lightDir)), 0.0);
			diffuse = diffuseObject * lightParameters[i].diffuse;
			ambient = ambientObject * lightParameters[i].ambient;
			if (NdotL>0.0){
				spotEffect = dot (normalize(lightParameters[i].spotDirection), normalize(-lightDir));
				if (spotEffect > lightParameters[i].spotCosCutoff){
					spotEffect = pow(spotEffect, lightParameters[i].spotExponent);
					att = spotEffect/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);
					finalLight+= att*(NdotL * diffuse + ambient);
					float NdotRV;
					vec3 R = reflect(-normalize(lightDir), fNormal);
					vec3 V = normalize(eyePos-fPosition);
					NdotRV = max(dot(R,V), 0.0);
					specular = specularObject * lightParameters[i].specular * pow(NdotRV, lightParameters[i].shininness);
					finalLight += att*(specular);
				}
			}
		}
	}

	mat3 tbn = mat3(fTangent, fBitangent, fNormal);
	vec3 BumpNorm = vec3(texture(normalSampler, UV.xy));
	vec3 DecalCol = vec3(texture(textureSampler, UV.xy));
	BumpNorm = tbn * ((BumpNorm - 0.5) * 2.0);
	float NL = max(dot(BumpNorm, normalize(lightDir)), 0.0);
	vec3 newDiffuse = NL*mix(DecalCol,finalLight, vec3(0.5,0.5,0.5));
	vFragColor = vec4(newDiffuse, 1.0);
}

