#include "Scene.h"

CScene::CScene(){
	//Load from JSON
	loadLights();
	eyePos[0] = eyePos[1] = eyePos[2] = 0;
	initShaders();
}

CScene::~CScene(){

}

void CScene::loadObjects()
{
	CTexturedObject* mOb = new CTexturedObject("./Assets/Models/Floor.obj", "./Assets/Textures/Floor.png");
	mOb->getTexture()->loadTexture("./Assets/Textures/FloorNormal.png");
	texturedObjects.push_back(mOb);
}

void CScene::loadLights()
{
	FILE* lightPath = fopen("./Assets/JSON/lights.json", "rb");
	if (lightPath == NULL){
		std::cout << "No se pudo abrir lights.json" << std::endl;
	}
	else{
		char mBuffer[1000];
		rapidjson::FileReadStream is(lightPath, mBuffer, sizeof(mBuffer));
		mDocument.ParseStream(is);

		rapidjson::Value& val = mDocument["lightParameters"];
		for (int i = 0; i < 2; i++)
		{
			mLights[i].type = val[i]["type"].GetInt(); //Direccional
			mLights[i].position = glm::vec3(val[i]["position"][0].GetDouble(), val[i]["position"][1].GetDouble(), val[i]["position"][2].GetDouble());
			mLights[i].diffuse = glm::vec3(val[i]["diffuse"][0].GetDouble(), val[i]["diffuse"][1].GetDouble(), val[i]["diffuse"][2].GetDouble());
			mLights[i].specular = glm::vec3(val[i]["specular"][0].GetDouble(), val[i]["specular"][1].GetDouble(), val[i]["specular"][2].GetDouble());
			mLights[i].ambient = glm::vec3(val[i]["ambient"][0].GetDouble(), val[i]["ambient"][1].GetDouble(), val[i]["ambient"][2].GetDouble());
			mLights[i].shininness = val[i]["shininness"].GetDouble();
			mLights[i].constantAttenuation = val[i]["constantAttenuation"].GetDouble();
			mLights[i].linearAttenuation = val[i]["linearAttenuation"].GetDouble();
			mLights[i].quadraticAttenuation = val[i]["quadraticAttenuation"].GetDouble();
			mLights[i].spotDirection = glm::vec3(val[i]["spotDirection"][0].GetDouble(), val[i]["spotDirection"][1].GetDouble(), val[i]["spotDirection"][2].GetDouble());
			mLights[i].spotExponent = val[i]["spotExponent"].GetDouble();
			mLights[i].spotCutoff = val[i]["spotCutoff"].GetDouble();
			mLights[i].spotCosCutoff = glm::cos(mLights[i].spotCutoff);
		}
		rapidjson::Value& valAmb = mDocument["ambientScene"];
		ambient = glm::vec3(valAmb[0].GetDouble(), valAmb[1].GetDouble(), valAmb[2].GetDouble());

		fclose(lightPath);
	}
}

void CScene::saveLights()
{
	FILE* lightPath = fopen("./Assets/JSON/lights.json", "wb");
	char writeBuffer[1000];
	rapidjson::FileWriteStream os(lightPath, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	mDocument.Accept(writer);
	fclose(lightPath);
}

void CScene::initShaders() {
	//Select-------------------------------------------------------------------------------------------------
	selection_program.loadShader("./Assets/shaders/basic.vert", CGLSLProgram::VERTEX);
	selection_program.loadShader("./Assets/shaders/select.frag", CGLSLProgram::FRAGMENT);
	//Link the shaders in a program
	selection_program.create_link();
	//Enable the program
	selection_program.enable();
	//Link the attributes and the uniforms
	selection_program.addAttribute("vVertex");
	selection_program.addAttribute("vColor");
	selection_program.addAttribute("vNormal");
	selection_program.addUniform("mProjection");
	selection_program.addUniform("mModelView");

	selection_program.addUniform("centerPosition");
	selection_program.addUniform("translateFactor");
	selection_program.addUniform("scaleFactor");
	selection_program.addUniform("quat");

	selection_program.addUniform("lightIndex");
	selection_program.addUniform("ambient");
	selection_program.addUniform("diffuse");
	selection_program.addUniform("specular");
	selection_program.addUniform("position");

	selection_program.addUniform("code");

	//Disable the program
	selection_program.disable();

	//Phong -------------------------------------------------------------------------------------------------
	//Load the shaders
	phong_program.loadShader("./Assets/shaders/basic.vert", CGLSLProgram::VERTEX);
	phong_program.loadShader("./Assets/shaders/phong.frag", CGLSLProgram::FRAGMENT);
	//Link the shaders in a program
	phong_program.create_link();
	//Enable the program
	phong_program.enable();
	//Link the attributes and the uniforms
	phong_program.addAttribute("vVertex");
	phong_program.addAttribute("vColor");
	phong_program.addAttribute("vNormal");
	phong_program.addAttribute("vTexture");
	phong_program.addAttribute("vTangent");
	phong_program.addUniform("vBitangent");
	phong_program.addUniform("mProjection");
	phong_program.addUniform("mModelView");

	phong_program.addUniform("centerPosition");
	phong_program.addUniform("translateFactor");
	phong_program.addUniform("scaleFactor");
	phong_program.addUniform("quat");

	phong_program.addUniform("lightIndex");
	phong_program.addUniform("ambient");
	phong_program.addUniform("diffuse");
	phong_program.addUniform("specular");
	phong_program.addUniform("position");

	for (int i = 0; i < 2; i++){
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].type");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].ambient");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].diffuse");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].specular");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].position");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].shininness");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].constantAttenuation");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].linearAttenuation");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].quadraticAttenuation");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].spotDirection");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].spotExponent");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCutoff");
		phong_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCosCutoff");
	}

	phong_program.addUniform("eyePos");

	phong_program.addUniform("diffuseObject");
	phong_program.addUniform("specularObject");
	phong_program.addUniform("ambientObject");
	phong_program.addUniform("sceneAmbient");
	//Constantes del modelo cook torrance
	phong_program.addUniform("roughnessValue");
	phong_program.addUniform("fresnelValue");
	phong_program.addUniform("gaussConstant");
	//Texturas
	phong_program.addUniform("textureSampler");
	phong_program.addUniform("normalSampler");
	//Disable the program
	phong_program.disable();

}

void CScene::setProjectionMatrix(const glm::mat4x4 &mProjectionMatrix)
{
	this->mProjectionMatrix = mProjectionMatrix;
}

void CScene::setModelViewMatrix(const glm::mat4x4 &mModelViewMatrix)
{
	this->mModelViewMatrix = mModelViewMatrix;
}

void CScene::setLightType(int i, int lightType){
	mLights[i].type = lightType;
	rapidjson::Value& val = mDocument["lightParameters"][i]["type"];
	val = lightType;
}

void CScene::setLightPos(int i, glm::vec3 lightPos)
{
	mLights[i].position = lightPos;
	rapidjson::Value& val = mDocument["lightParameters"][i]["position"];
	val[0] = lightPos.x;
	val[1] = lightPos.y;
	val[2] = lightPos.z;

		/*objects[i+4]->setTransFX(lightPos.x);
		objects[i+4]->setTransFY(lightPos.y);
		objects[i+4]->setTransFZ(lightPos.z);
		*/
}

void CScene::setEyePos(glm::vec3 eyePos)
{
	this->eyePos = eyePos;

}

void CScene::setDiffuse(int i, glm::vec3 ld)
{
	mLights[i].diffuse = ld;
	rapidjson::Value& val = mDocument["lightParameters"][i]["diffuse"];
	val[0] = ld.x;
	val[1] = ld.y;
	val[2] = ld.z;
}

void CScene::setSpecular(int i, glm::vec3 ls)
{
	mLights[i].specular = ls;
	rapidjson::Value& val = mDocument["lightParameters"][i]["specular"];
	val[0] = ls.x;
	val[1] = ls.y;
	val[2] = ls.z;
}

void CScene::setAmbient(glm::vec3 ambient) //El color ambiental de la escena
{
	this->ambient = ambient;
	rapidjson::Value& val = mDocument["ambientScene"];
	val[0] = ambient.x;
	val[1] = ambient.y;
	val[2] = ambient.z;
}

void CScene::setAmbient(int i, glm::vec3 ambient) 
{
	mLights[i].ambient = ambient;
	rapidjson::Value& val = mDocument["lightParameters"][i]["ambient"];
	val[0] = ambient.x;
	val[1] = ambient.y;
	val[2] = ambient.z;
}

void CScene::setConstantAttenuation(int i, float param)
{
	mLights[i].constantAttenuation = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["constantAttenuation"];
	val = param;
}

void CScene::setShininness(int i, float param)
{
	mLights[i].shininness = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["shininness"];
	val = param;
}

void CScene::setLinearAttenuation(int i, float param)
{
	mLights[i].linearAttenuation = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["linearAttenuation"];
	val = param;
}

void CScene::setQuadraticAttenuation(int i, float param)
{
	mLights[i].quadraticAttenuation = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["quadraticAttenuation"];
	val = param;
}

void CScene::setSpotDirection(int i, glm::vec3 param)
{
	mLights[i].spotDirection = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["spotDirection"];
	val[0] = param.x;
	val[1] = param.y;
	val[2] = param.z;
}

void CScene::setSpotExponent(int i, float param)
{
	mLights[i].spotExponent = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["spotExponent"];
	val = param;
}

void CScene::setSpotCutoff(int i, float param)
{
	mLights[i].spotCutoff = param;
	rapidjson::Value& val = mDocument["lightParameters"][i]["spotCutoff"];
	val = param;

	mLights[i].spotCosCutoff = glm::cos(param);
	rapidjson::Value& val2 = mDocument["lightParameters"][i]["spotCosCutoff"];
	val2 = glm::cos(param);
}

glm::mat4x4 CScene::getProjectionMatrix()
{
	return mProjectionMatrix;
}

glm::mat4x4 CScene::getModelViewMatrix()
{
	return mModelViewMatrix;
}

glm::vec3 CScene::getEyePos()
{
	return eyePos;
}

glm::vec3 CScene::getAmbient()
{
	return ambient;
}

std::vector<CObject*> CScene::getObjects()
{
	return objects;
}

std::vector<CTexturedObject*> CScene::getTexturedObjects()
{
	return texturedObjects;
}

CObject* CScene::getObject(int i)
{
	return objects[i];
}

CTexturedObject* CScene::getTexturedObject(int i)
{
	return texturedObjects[i];
}

std::vector<CGLSLProgram*> CScene::getProgram(){
	std::vector<CGLSLProgram*> programs;
	programs.push_back(&phong_program);
	programs.push_back(&selection_program);
	return programs;
}

lightParameters* CScene::getLights()
{
	return mLights;
}

LightParameters CScene::getLight(int i)
{
	return mLights[i];
}