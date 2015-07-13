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

void main(){
    //CONSTANTES - PASAR EN VERTEX - r1?
    //float roughnessValue = 1.0; // 0 : smooth, 1: rough
	//float F0 = 0.10; // fresnel reflectance

	vec3 lightDir;
	vec3 finalLight = sceneAmbient * ambientObject;
	float distance, NdotL, Rs = 1.0, att = 1.0;
	vec3 normal = normalize(fNormal);
	vec3 eyeDir = normalize(eyePos);
	float fresnel, roughness, geoAtt;

	for (int i=0; i<3; i++)	{
		if (lightParameters[i].type == 1){ //Direccional
			lightDir = normalize(lightParameters[i].position-fPosition);    		
			NdotL = max(dot(normal, lightDir), 0.0);

			if(NdotL > 0.0){
				vec3 halfVector = normalize(lightDir + eyeDir);
				float NdotH = max(dot(normal, halfVector), 0.0); 
				float NdotV = max(dot(normal, eyeDir), 0.0); 
				float VdotH = max(dot(eyeDir, halfVector), 0.0);
				float mSquared = roughnessValue * roughnessValue;
        
				// geometric attenuation
				float NH2 = 2.0 * NdotH;
				float g1 = (NH2 * NdotV) / VdotH;
				float g2 = (NH2 * NdotL) / VdotH;
				geoAtt = min(1.0, min(g1, g2));
     
				// roughness
				//float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
				float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
				roughness = gaussConstant * exp(r2);
        
				// fresnel
				fresnel = pow(1.0 - VdotH, 5.0);
				fresnel = fresnel * (1.0 - fresnelValue);
				fresnel = fresnel + fresnelValue;
        
				Rs = (fresnel * geoAtt * roughness) / (NdotL * NdotL * 3.14);
			}
			finalLight += ambientObject * max(NdotL, 0.0) * (diffuseObject + Rs * specularObject);
		}else if (lightParameters[i].type == 2){ //Puntual
			lightDir = normalize(lightParameters[i].position-fPosition);    		
			distance = length(lightDir);
			NdotL = max(dot(normal, lightDir), 0.0);

			if(NdotL > 0.0){
				vec3 halfVector = normalize(lightDir + eyeDir);
				float NdotH = max(dot(normal, halfVector), 0.0); 
				float NdotV = max(dot(normal, eyeDir), 0.0); 
				float VdotH = max(dot(eyeDir, halfVector), 0.0);
				float mSquared = roughnessValue * roughnessValue;
				att = 1.0/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);

				// geometric attenuation
				float NH2 = 2.0 * NdotH;
				float g1 = (NH2 * NdotV) / VdotH;
				float g2 = (NH2 * NdotL) / VdotH;
				geoAtt = min(1.0, min(g1, g2));
     
				// roughness
				//float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
				float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
				roughness = gaussConstant * exp(r2);
        
				// fresnel
				fresnel = pow(1.0 - VdotH, 5.0);
				fresnel = fresnel * (1.0 - fresnelValue);
				fresnel = fresnel + fresnelValue;
        
				Rs = (fresnel * geoAtt * roughness) / (NdotL * NdotL * 3.14);
			}
			finalLight += att * ambientObject * max(NdotL, 0.0) * (diffuseObject + Rs * specularObject);
		}else if (lightParameters[i].type == 3){ //Reflector
			lightDir = normalize(lightParameters[i].position-fPosition);    		
			distance = length(lightDir);
			NdotL = max(dot(normal, lightDir), 0.0);

			if(NdotL > 0.0){
				vec3 halfVector = normalize(lightDir + eyeDir);
				float NdotH = max(dot(normal, halfVector), 0.0); 
				float NdotV = max(dot(normal, eyeDir), 0.0); 
				float VdotH = max(dot(eyeDir, halfVector), 0.0);
				float mSquared = roughnessValue * roughnessValue;
				float spotEffect = dot (normalize(lightParameters[i].spotDirection), normalize(-lightDir));
				if (spotEffect > lightParameters[i].spotCosCutoff){
					spotEffect = pow(spotEffect, lightParameters[i].spotExponent);
					att = spotEffect/(lightParameters[i].constantAttenuation + lightParameters[i].linearAttenuation + lightParameters[i].quadraticAttenuation * distance * distance);
					// geometric attenuation
					float NH2 = 2.0 * NdotH;
					float g1 = (NH2 * NdotV) / VdotH;
					float g2 = (NH2 * NdotL) / VdotH;
					geoAtt = min(1.0, min(g1, g2));
     
					// roughness
					float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
					float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
					roughness = 100 * exp(r2);
        
					// fresnel
					fresnel = pow(1.0 - VdotH, 5.0);
					fresnel = fresnel * (1.0 - fresnelValue);
					fresnel = fresnel + fresnelValue;

					Rs = (fresnel * geoAtt * roughness) / (NdotL * NdotL * 3.14);
					finalLight += att * ambientObject * max(NdotL, 0.0) * (diffuseObject + Rs * specularObject);
				}
			}
		}

		vFragColor = vec4(clamp(finalLight, vec3(0), vec3(1)), 1.0);

	}
}