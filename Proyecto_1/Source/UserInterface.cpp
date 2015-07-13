#include "UserInterface.h"

extern GLFWwindow* gpWindow;
extern int gWidth;
extern int gHeight;
extern CUserInterface *gpUserInterface;
extern CScene* gpScene;
extern int picked;

//Light 0 -----------------------------------------------------------------------------//
void TW_CALL lightTypeSet0(const void *value, void *clientData){
	gpScene->setLightType(0, (*(const int*)value));
}

void TW_CALL lightTypeGet0(void *value, void *clientData){
	*(int *)value = gpScene->getLight(0).type;  // for instance
}

void TW_CALL lightAmbientSet0(const void *value, void *clientData)
{
	gpScene->setAmbient(0, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightAmbientGet0(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(0).ambient.x;
	((GLfloat*)value)[1] = gpScene->getLight(0).ambient.y;
	((GLfloat*)value)[2] = gpScene->getLight(0).ambient.z;
}

void TW_CALL lightDiffuseSet0(const void *value, void *clientData)
{
	gpScene->setDiffuse(0, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightDiffuseGet0(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(0).diffuse.x;
	((GLfloat*)value)[1] = gpScene->getLight(0).diffuse.y;
	((GLfloat*)value)[2] = gpScene->getLight(0).diffuse.z;
}

void TW_CALL lightSpecularSet0(const void *value, void *clientData)
{
	gpScene->setSpecular(0, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpecularGet0(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(0).specular.x;
	((GLfloat*)value)[1] = gpScene->getLight(0).specular.y;
	((GLfloat*)value)[2] = gpScene->getLight(0).specular.z;
}

void TW_CALL lightPosSet0(const void *value, void *clientData)
{
	gpScene->setLightPos(0, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightPosGet0(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(0).position.x;
	((GLfloat*)value)[1] = gpScene->getLight(0).position.y;
	((GLfloat*)value)[2] = gpScene->getLight(0).position.z;
}

void TW_CALL lightShininnessSet0(const void *value, void *clientData)
{
	gpScene->setShininness(0, (*(const float*)value));
}

void TW_CALL lightShininnessGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).shininness;  // for instance
}

void TW_CALL lightConstantAttenuationSet0(const void *value, void *clientData)
{
	gpScene->setConstantAttenuation(0, (*(const float*)value));
}

void TW_CALL lightConstantAttenuationGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).constantAttenuation;  // for instance
}

void TW_CALL lightLinearAttenuationSet0(const void *value, void *clientData)
{
	gpScene->setLinearAttenuation(0, (*(const float*)value));
}

void TW_CALL lightLinearAttenuationGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).linearAttenuation;  // for instance
}

void TW_CALL lightQuadraticAttenuationSet0(const void *value, void *clientData)
{
	gpScene->setQuadraticAttenuation(0, (*(const float*)value));
}

void TW_CALL lightQuadraticAttenuationGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).quadraticAttenuation;  // for instance
}

void TW_CALL lightSpotDirectionSet0(const void *value, void *clientData)
{
	gpScene->setSpotDirection(0, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpotDirectionGet0(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(0).spotDirection.x;
	((GLfloat*)value)[1] = gpScene->getLight(0).spotDirection.y;
	((GLfloat*)value)[2] = gpScene->getLight(0).spotDirection.z;
}

void TW_CALL lightSpotExponentSet0(const void *value, void *clientData)
{
	gpScene->setSpotExponent(0, (*(const float*)value));
}

void TW_CALL lightSpotExponentGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).spotExponent;  // for instance
}

void TW_CALL lightSpotCutoffSet0(const void *value, void *clientData)
{
	gpScene->setSpotCutoff(0, (*(const float*)value));
}

void TW_CALL lightSpotCutoffGet0(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(0).spotCutoff;  // for instance
}

//Light 1--------------------------------------------------------------------------//
void TW_CALL lightTypeSet1(const void *value, void *clientData){
	gpScene->setLightType(1, *(int *)value);
}

void TW_CALL lightTypeGet1(void *value, void *clientData){
	*(int *)value = gpScene->getLight(1).type;  // for instance
}

void TW_CALL lightAmbientSet1(const void *value, void *clientData)
{
	gpScene->setAmbient(1, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightAmbientGet1(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(1).ambient.x;
	((GLfloat*)value)[1] = gpScene->getLight(1).ambient.y;
	((GLfloat*)value)[2] = gpScene->getLight(1).ambient.z;
}

void TW_CALL lightDiffuseSet1(const void *value, void *clientData)
{
	gpScene->setDiffuse(1, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightDiffuseGet1(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(1).diffuse.x;
	((GLfloat*)value)[1] = gpScene->getLight(1).diffuse.y;
	((GLfloat*)value)[2] = gpScene->getLight(1).diffuse.z;
}

void TW_CALL lightSpecularSet1(const void *value, void *clientData)
{
	gpScene->setSpecular(1, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpecularGet1(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(1).specular.x;
	((GLfloat*)value)[1] = gpScene->getLight(1).specular.y;
	((GLfloat*)value)[2] = gpScene->getLight(1).specular.z;
}

void TW_CALL lightPosSet1(const void *value, void *clientData)
{
	gpScene->setLightPos(1, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightPosGet1(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(1).position.x;
	((GLfloat*)value)[1] = gpScene->getLight(1).position.y;
	((GLfloat*)value)[2] = gpScene->getLight(1).position.z;
}

void TW_CALL lightShininnessSet1(const void *value, void *clientData)
{
	gpScene->setShininness(1, (*(const float*)value));
}

void TW_CALL lightShininnessGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).shininness;  // for instance
}

void TW_CALL lightConstantAttenuationSet1(const void *value, void *clientData)
{
	gpScene->setConstantAttenuation(1, (*(const float*)value));
}

void TW_CALL lightConstantAttenuationGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).constantAttenuation;  // for instance
}

void TW_CALL lightLinearAttenuationSet1(const void *value, void *clientData)
{
	gpScene->setLinearAttenuation(1, (*(const float*)value));
}

void TW_CALL lightLinearAttenuationGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).linearAttenuation;  // for instance
}

void TW_CALL lightQuadraticAttenuationSet1(const void *value, void *clientData)
{
	gpScene->setQuadraticAttenuation(1, (*(const float*)value));
}

void TW_CALL lightQuadraticAttenuationGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).quadraticAttenuation;  // for instance
}

void TW_CALL lightSpotDirectionSet1(const void *value, void *clientData)
{
	gpScene->setSpotDirection(1, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpotDirectionGet1(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(1).spotDirection.x;
	((GLfloat*)value)[1] = gpScene->getLight(1).spotDirection.y;
	((GLfloat*)value)[2] = gpScene->getLight(1).spotDirection.z;
}

void TW_CALL lightSpotExponentSet1(const void *value, void *clientData)
{
	gpScene->setSpotExponent(1, (*(const float*)value));
}

void TW_CALL lightSpotExponentGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).spotExponent;  // for instance
}

void TW_CALL lightSpotCutoffSet1(const void *value, void *clientData)
{
	gpScene->setSpotCutoff(1, (*(const float*)value));
}

void TW_CALL lightSpotCutoffGet1(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(1).spotCutoff;  // for instance
}

//Light 2 -------------------------------------------------------------------------//
void TW_CALL lightTypeSet2(const void *value, void *clientData){
	gpScene->setLightType(2, *(int *)value);
}

void TW_CALL lightTypeGet2(void *value, void *clientData){
	*(int *)value = gpScene->getLight(2).type;  // for instance
}

void TW_CALL lightAmbientSet2(const void *value, void *clientData)
{
	gpScene->setAmbient(2, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightAmbientGet2(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(2).ambient.x;
	((GLfloat*)value)[1] = gpScene->getLight(2).ambient.y;
	((GLfloat*)value)[2] = gpScene->getLight(2).ambient.z;
}

void TW_CALL lightDiffuseSet2(const void *value, void *clientData)
{
	gpScene->setDiffuse(2, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightDiffuseGet2(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(2).diffuse.x;
	((GLfloat*)value)[1] = gpScene->getLight(2).diffuse.y;
	((GLfloat*)value)[2] = gpScene->getLight(2).diffuse.z;
}

void TW_CALL lightSpecularSet2(const void *value, void *clientData)
{
	gpScene->setSpecular(2, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpecularGet2(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(2).specular.x;
	((GLfloat*)value)[1] = gpScene->getLight(2).specular.y;
	((GLfloat*)value)[2] = gpScene->getLight(2).specular.z;
}

void TW_CALL lightPosSet2(const void *value, void *clientData)
{
	gpScene->setLightPos(2, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightPosGet2(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(2).position.x;
	((GLfloat*)value)[1] = gpScene->getLight(2).position.y;
	((GLfloat*)value)[2] = gpScene->getLight(2).position.z;
}

void TW_CALL lightShininnessSet2(const void *value, void *clientData)
{
	gpScene->setShininness(2, (*(const float*)value));
}

void TW_CALL lightShininnessGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).shininness;  // for instance
}

void TW_CALL lightConstantAttenuationSet2(const void *value, void *clientData)
{
	gpScene->setConstantAttenuation(2, (*(const float*)value));
}

void TW_CALL lightConstantAttenuationGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).constantAttenuation;  // for instance
}

void TW_CALL lightLinearAttenuationSet2(const void *value, void *clientData)
{
	gpScene->setLinearAttenuation(2, (*(const float*)value));
}

void TW_CALL lightLinearAttenuationGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).linearAttenuation;  // for instance
}

void TW_CALL lightQuadraticAttenuationSet2(const void *value, void *clientData)
{
	gpScene->setQuadraticAttenuation(2, (*(const float*)value));
}

void TW_CALL lightQuadraticAttenuationGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).quadraticAttenuation;  // for instance
}

void TW_CALL lightSpotDirectionSet2(const void *value, void *clientData)
{
	gpScene->setSpotDirection(2, glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL lightSpotDirectionGet2(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getLight(2).spotDirection.x;
	((GLfloat*)value)[1] = gpScene->getLight(2).spotDirection.y;
	((GLfloat*)value)[2] = gpScene->getLight(2).spotDirection.z;
}

void TW_CALL lightSpotExponentSet2(const void *value, void *clientData)
{
	gpScene->setSpotExponent(2, (*(const float*)value));
}

void TW_CALL lightSpotExponentGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).spotExponent;  // for instance
}

void TW_CALL lightSpotCutoffSet2(const void *value, void *clientData)
{
	gpScene->setSpotCutoff(2, (*(const float*)value));
}

void TW_CALL lightSpotCutoffGet2(void *value, void *clientData)
{
	*(float *)value = gpScene->getLight(2).spotCutoff;  // for instance
}

//Object --------------------------------------------------------------------------------------------------------
void TW_CALL objectDiffuseSet(const void *value, void *clientData)
{
	gpScene->getTexturedObject(picked)->setDiffuseObject(glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL objectDiffuseGet(void *value, void *clientData)
{
	((float*)value)[0] = gpScene->getTexturedObject(picked)->getDiffuseObject().x;
	((float*)value)[1] = gpScene->getTexturedObject(picked)->getDiffuseObject().y;
	((float*)value)[2] = gpScene->getTexturedObject(picked)->getDiffuseObject().z;
}

void TW_CALL objectSpecularSet(const void *value, void *clientData)
{
	gpScene->getTexturedObject(picked)->setSpecularObject(glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL objectSpecularGet(void *value, void *clientData)
{
	((float*)value)[0] = gpScene->getTexturedObject(picked)->getSpecularObject().x;
	((float*)value)[1] = gpScene->getTexturedObject(picked)->getSpecularObject().y;
	((float*)value)[2] = gpScene->getTexturedObject(picked)->getSpecularObject().z;
}

void TW_CALL objectAmbientSet(const void *value, void *clientData)
{
	gpScene->getTexturedObject(picked)->setAmbientObject(glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL objectAmbientGet(void *value, void *clientData)
{
	((float*)value)[0] = gpScene->getTexturedObject(picked)->getAmbientObject().x;
	((float*)value)[1] = gpScene->getTexturedObject(picked)->getAmbientObject().y;
	((float*)value)[2] = gpScene->getTexturedObject(picked)->getAmbientObject().z;
}

//Scene --------------------------------------------------------------------------------------------------------
void TW_CALL sceneAmbientSet(const void *value, void *clientData)
{
	gpScene->setAmbient(glm::vec3(((float*)value)[0], ((float*)value)[1], ((float*)value)[2]));
}

void TW_CALL sceneAmbientGet(void *value, void *clientData)
{
	((GLfloat*)value)[0] = gpScene->getAmbient().x;
	((GLfloat*)value)[1] = gpScene->getAmbient().y;
	((GLfloat*)value)[2] = gpScene->getAmbient().z;
}


//JSON -------------------------------------------------------------------------------------------------------
void TW_CALL saveJSON(void *clientData)
{
	gpScene->saveLights();
}

CUserInterface::CUserInterface(){
	mBar = TwNewBar("lightsBar");
	TwDefine("lightsBar refresh = '0.0001f'");
	TwDefine("lightsBar resizable = false");
	TwDefine("lightsBar fontresizable = false");
	TwDefine("lightsBar movable = false");
	TwDefine("lightsBar visible = true");
	TwDefine("lightsBar position = '20 20'");
	TwDefine("lightsBar size = '270 560'");

	TwAddButton(mBar, "", saveJSON, NULL, "label='Guardar JSON'");

	//Object 
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, objectDiffuseSet, objectDiffuseGet, &diffuseObject[0], "group='Objecto' label='Diffuse Object'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, objectSpecularSet, objectSpecularGet, &specularObject[0], "group='Objecto' label='Specular Object'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, objectAmbientSet, objectAmbientGet, &ambientObject[0], "group='Objecto' label='Ambient Object'");

	//Scene
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, sceneAmbientSet, sceneAmbientGet, &sceneAmbient[0], "group='Scene' label='Ambient Scene'");

	//Leyenda
	TwAddButton(mBar, "", NULL, NULL, "label='Lights Type:'");
	TwAddButton(mBar, "", NULL, NULL, "label='1-Direccional'");
	TwAddButton(mBar, "", NULL, NULL, "label='2-Puntual'");
	TwAddButton(mBar, "", NULL, NULL, "label='3-Spotlight'");
	TwAddButton(mBar, "", NULL, NULL, "label='4-Apagada'");

	//Light 0	
	TwAddVarCB(mBar, "", TW_TYPE_INT16, lightTypeSet0, lightTypeGet0, &mLights[0].type, "group='Luz 1' label='Type' step=1 max=4 min=1");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightAmbientSet0, lightAmbientGet0, &mLights[0].ambient, "group='Luz 1' label='Ambient'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightDiffuseSet0, lightDiffuseGet0, &mLights[0].diffuse, "group='Luz 1' label='Diffuse'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightSpecularSet0, lightSpecularGet0, &mLights[0].specular, "group='Luz 1' label='Specular'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightShininnessSet0, lightShininnessGet0, &mLights[0].shininness, "group='Luz 1' label='Shininness' step=0.01 min=0.0");
	TwAddVarCB(mBar, "", TW_TYPE_DIR3F, lightPosSet0, lightPosGet0, &mLights[0].position, "group='Luz 1' label='Position'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightConstantAttenuationSet0, lightConstantAttenuationGet0, &mLights[0].constantAttenuation, "group='Luz 1' label='Constant Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightLinearAttenuationSet0, lightLinearAttenuationGet0, &mLights[0].linearAttenuation, "group='Luz 1' label='Linear Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightQuadraticAttenuationSet0, lightQuadraticAttenuationGet0, &mLights[0].quadraticAttenuation, "group='Luz 1' label='Quadratic Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_DIR3F, lightSpotDirectionSet0, lightSpotDirectionGet0, &mLights[0].spotDirection, "group='Luz 1' label='Spot Direction'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightSpotExponentSet0, lightSpotExponentGet0, &mLights[0].spotExponent, "group='Luz 1' step=0.001 label='Spot Exponent'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightSpotCutoffSet0, lightSpotCutoffGet0, &mLights[0].spotCutoff, "group='Luz 1' step=0.001 label='Spot Cutoff'");

	//Light 1
	TwAddVarCB(mBar, "", TW_TYPE_INT16, lightTypeSet1, lightTypeGet1, &mLights[1].type, "group='Luz 2' label='Type' step = 1 max = 4 min = 1");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightAmbientSet1, lightAmbientGet1, &mLights[1].ambient, "group='Luz 2' label='Ambient'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightDiffuseSet1, lightDiffuseGet1, &mLights[1].diffuse, "group='Luz 2' label='Diffuse'");
	TwAddVarCB(mBar, "", TW_TYPE_COLOR3F, lightSpecularSet1, lightSpecularGet1, &mLights[1].specular, "group='Luz 2' label='Specular'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightShininnessSet1, lightShininnessGet1, &mLights[1].shininness, "group='Luz 2' label='Shininness' step=0.01 min=0.0");
	TwAddVarCB(mBar, "", TW_TYPE_DIR3F, lightPosSet1, lightPosGet1, &mLights[1].position, "group='Luz 2' label='Position2'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightConstantAttenuationSet1, lightConstantAttenuationGet1, &mLights[1].constantAttenuation, "group='Luz 2' label='Constant Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightLinearAttenuationSet1, lightLinearAttenuationGet1, &mLights[1].linearAttenuation, "group='Luz 2' label='Linear Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightQuadraticAttenuationSet1, lightQuadraticAttenuationGet1, &mLights[1].quadraticAttenuation, "group='Luz 2' label='Quadratic Attenuation'");
	TwAddVarCB(mBar, "", TW_TYPE_DIR3F, lightSpotDirectionSet1, lightSpotDirectionGet1, &mLights[1].spotDirection, "group='Luz 2' label='Spot Direction'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightSpotExponentSet1, lightSpotExponentGet1, &mLights[1].spotExponent, "group='Luz 2' step=0.001 label='Spot Exponent'");
	TwAddVarCB(mBar, "", TW_TYPE_FLOAT, lightSpotCutoffSet1, lightSpotCutoffGet1, &mLights[1].spotCutoff, "group='Luz 2' step=0.001 label='SpotCutoff'");
	}

CUserInterface::~CUserInterface(){
	//
}

void CUserInterface::reshape(){
	TwWindowSize(gWidth, gHeight);
}