#pragma once

#include "Object.h"
#include "TexturedObject.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\stringbuffer.h"

typedef struct LightParameters{
	int type;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	float shininness;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	glm::vec3 spotDirection;
	float spotExponent;
	float spotCutoff;
	float spotCosCutoff;
}lightParameters;


class CScene{
private:
	std::vector<CObject*> objects;
	std::vector<CTexturedObject*> texturedObjects;
	std::vector<CTexturedObject*> mirrors;

	std::vector<CObject*> lights;
	glm::mat4x4 mProjectionMatrix;
	glm::mat4x4 mModelViewMatrix;
	CGLSLProgram normal_program, selection_program, parallax_program, cubemap_program, skybox_program;
	glm::vec3 eyePos;
	lightParameters mLights[3];
	glm::vec3 ambient;
	rapidjson::Document mDocument;
	glm::vec3 P;
	glm::vec3 V;
	glm::mat4 R;

public:
	CScene();
	~CScene();
	void initShaders();
	void loadObjects();
	void loadLights();
	void saveLights();
	//Get and set
	void setProjectionMatrix(const glm::mat4x4 &mProjectionMatrix);
	void setModelViewMatrix(const glm::mat4x4 &mModelViewMatrix);
	void setLightType(int i, int lightType);
	void setLightPos(int i, glm::vec3 lightPos);
	void setEyePos(glm::vec3 eyePos);
	void setDiffuse(int i, glm::vec3 ld);
	void setSpecular(int i, glm::vec3 ls);
	void setAmbient(int i, glm::vec3 amb);
	void setAmbient(glm::vec3 ambient);
	void setConstantAttenuation(int i, float val);
	void setQuadraticAttenuation(int i, float val);
	void setLinearAttenuation(int i, float val);
	void setSpotDirection(int i, glm::vec3 val);
	void setSpotExponent(int i, float val);
	void setSpotCutoff(int i, float val);
	void setShininness(int i, float param);
	glm::mat4x4 getProjectionMatrix();
	glm::mat4x4 getModelViewMatrix();
	glm::vec3 getLightPos();
	glm::vec3 getEyePos();
	glm::vec3 getLd();
	glm::vec3 getLs();
	glm::vec3 getAmbient();
	std::vector<CObject*> getObjects();
	std::vector<CTexturedObject*> getTexturedObjects();
	std::vector<CTexturedObject*> getMirrors();
	CObject* getObject(int i);
	CTexturedObject* getTexturedObject(int i);
	std::vector<CGLSLProgram*> getProgram();
	lightParameters* getLights();
	LightParameters getLight(int i);
};