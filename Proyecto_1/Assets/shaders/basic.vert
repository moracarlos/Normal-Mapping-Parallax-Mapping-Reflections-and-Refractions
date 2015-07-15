#version 330

uniform mat4 mProjection, mModelView;
uniform vec3 scaleFactor, translateFactor, centerPosition, eyePos;
uniform vec4 quat;

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexture;
layout(location = 4) in vec3 vTangent;
layout(location = 5) in vec3 vBitangent;

out vec3 vVertexColor;
out vec3 fNormal;
out vec3 fPosition;
out vec2 UV;
out vec3 fTangent;
out vec3 fBitangent;
out vec3 eyeVec;

void main()
{
	fTangent = vTangent;
	fBitangent = vBitangent;
    //Calcular la matriz normal
    //Transformaciones
    vVertexColor = clamp(vNormal,0,1);
    mat4 returnFig = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(centerPosition[0],centerPosition[1],centerPosition[2]-0,1)); //-10
    mat4 centerFig = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(-centerPosition[0],-centerPosition[1],-centerPosition[2]+0,1)); //+10
    mat4 translateMatrix=mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(translateFactor[0], translateFactor[1], translateFactor[2],1));
    mat4 scaleMatrix = mat4(vec4(scaleFactor[0],0,0,0), vec4(0,scaleFactor[1],0,0), vec4(0,0,scaleFactor[2],0), vec4(0,0,0,1));
    mat4 rotateMatrix;

    rotateMatrix[0][0] = 1.0f - 2.0f * (quat[1] * quat[1] + quat[2] * quat[2]);
    rotateMatrix[0][1] = 2.0f * (quat[0] * quat[1] + quat[2] * quat[3]);
    rotateMatrix[0][2] = 2.0f * (quat[0] * quat[2] - quat[1] * quat[3]);
    rotateMatrix[0][3] = 0.0f;
    rotateMatrix[1][0] = 2.0f * (quat[0] * quat[1] - quat[2] * quat[3]);
    rotateMatrix[1][1] = 1.0f - 2.0f * (quat[0] * quat[0] + quat[2] * quat[2]);
    rotateMatrix[1][2] = 2.0f * (quat[1] * quat[2] + quat[0] * quat[3]);
    rotateMatrix[1][3] = 0.0f;
    rotateMatrix[2][0] = 2.0f * (quat[0] * quat[2] + quat[1] * quat[3]);
    rotateMatrix[2][1] = 2.0f * (quat[1] * quat[2] - quat[0] * quat[3]);
    rotateMatrix[2][2] = 1.0f - 2.0f * (quat[0] * quat[0] + quat[1] * quat[1]);
    rotateMatrix[2][3] = 0.0f;
    rotateMatrix[3][0] = 0.0f;
    rotateMatrix[3][1] = 0.0f;
    rotateMatrix[3][2] = 0.0f;
    rotateMatrix[3][3] = 1.0f;
    
	mat4 MV = translateMatrix* returnFig*rotateMatrix*scaleMatrix*centerFig*mModelView;

	mat3 normalMatrix;
	mat4 invTransp = inverse(transpose(MV));
	normalMatrix = mat3(vec3(invTransp[0][0], invTransp[0][1], invTransp[0][2]), vec3(invTransp[1][0], invTransp[1][1], invTransp[1][2]), vec3(invTransp[2][0], invTransp[2][1], invTransp[2][2]));
	
	UV = vTexture;
	fNormal = normalize(normalMatrix * vNormal);

	mat3 tbn = mat3(fTangent, fBitangent, fNormal);
	eyeVec = tbn * (eyePos - vVertex);

	vec4 pos = MV * vec4(vVertex, 1.0);
	fPosition = pos.xyz;
	gl_Position = mProjection * pos;
}
