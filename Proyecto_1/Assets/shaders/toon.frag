#version 330
#extension GL_ARB_separate_shader_objects :enable

#define NUMLIGHTS 3
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



layout(location = 0) out vec4 vFragColor;

void main(void)
{
	vec3 eyeDir;
	vec3 lightDir;
	vec3 finalLight;
	float intensity;
	float distance;
	float att;
	float spotEffect;
	float NdotL;
	finalLight = vec3(0,0,0);
	eyeDir = normalize(eyePos-fPosition);
	for (int i=0; i<3; i++)
	{
		if (lightParameters[i].type == 1){
			lightDir = normalize(lightParameters[i].position-fPosition);
			NdotL = max(dot(fNormal, normalize(lightDir)), 0.0);
			if (max(0.0,dot(eyeDir, fNormal))>0.0){
				intensity = dot(lightDir,fNormal);
				if (intensity > 0.95)
					finalLight += vec3(1.0,0.5,0.5)*lightParameters[i].diffuse;
				else if (intensity > 0.5)
					finalLight += vec3(0.6,0.3,0.3)*lightParameters[i].diffuse;
				else if (intensity > 0.25)
					finalLight += vec3(0.4,0.2,0.2)*lightParameters[i].diffuse;
				else
					finalLight += vec3(0.2,0.1,0.1)*lightParameters[i].diffuse;
			}
		}
		else if (lightParameters[i].type == 2){ //Puntual
			lightDir = lightParameters[i].position-fPosition;
			distance = length(lightDir);
			NdotL = max(dot(fNormal, normalize(lightDir)), 0.0);
			if (max(0.0,dot(eyeDir, fNormal))>0.0){
				att = 1.0/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);
				intensity = dot(normalize(lightDir),fNormal);
				intensity = intensity * att; 
				if (intensity > 0.95)
					finalLight += vec3(1.0,0.5,0.5)*lightParameters[i].diffuse;
				else if (intensity > 0.5)
					finalLight += vec3(0.6,0.3,0.3)*lightParameters[i].diffuse;
				else if (intensity > 0.25)
					finalLight += vec3(0.4,0.2,0.2)*lightParameters[i].diffuse;
				else
					finalLight += vec3(0.2,0.1,0.1)*lightParameters[i].diffuse;
			}
		}
		else if (lightParameters[i].type == 3){
			lightDir = lightParameters[i].position-fPosition;
			NdotL = max(dot(fNormal, normalize(lightDir)), 0.0);
			if (max(0.0,dot(eyeDir, fNormal))>0.0){
				distance = length(lightDir);
				spotEffect = dot (normalize(lightParameters[i].spotDirection), normalize(-lightDir));
				if (spotEffect > lightParameters[i].spotCosCutoff){
					spotEffect = pow(spotEffect, lightParameters[i].spotExponent);
					att = spotEffect/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);
					intensity = dot(normalize(lightDir),fNormal);
					intensity = intensity * att;
					if (intensity > 0.95)
						finalLight += vec3(1.0,0.5,0.5)*lightParameters[i].diffuse;
					else if (intensity > 0.5)
						finalLight += vec3(0.6,0.3,0.3)*lightParameters[i].diffuse;
					else if (intensity > 0.25)
						finalLight += vec3(0.4,0.2,0.2)*lightParameters[i].diffuse;
					else
						finalLight += vec3(0.2,0.1,0.1)*lightParameters[i].diffuse; 
				}
			}
		}
	}
	vFragColor = vec4(clamp(finalLight, vec3(0), vec3(1)), 1.0);
}

