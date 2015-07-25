#include "Scene.h"

CScene::CScene(){
	//Load from JSON
	loadLights();
	eyePos[0] = eyePos[1] = eyePos[2] = 0;
	initShaders();

	P = glm::vec3(0, 0, 0);
	V = glm::vec3(0, 1, 0);
	R = glm::mat4(
		1.0 - 2 * V.x*V.x, -2 * V.x*V.y, -2 * V.x*V.z, 2 * (glm::dot(P, V))*V.x,
		-2 * V.x*V.y, 1 - 2 * V.y*V.y, -2 * V.y*V.z, 2 * (glm::dot(P, V))*V.y,
		-2 * V.x*V.z, -2 * V.y*V.z, 1 - 2 * V.z*V.z, 2 * (glm::dot(P, V))*V.z,
		0, 0, 0, 1
		);
}

CScene::~CScene(){

}

void CScene::loadObjects()
{
	//CTexturedObject* mOb = new CTexturedObject("./Assets/Models/Floor.obj", "./Assets/Textures/Floor.png");
	//mOb->getTexture()->loadTexture("./Assets/Textures/FloorNormal.png");
	CTexturedObject* mOb = new CTexturedObject("./Assets/Models/piso.obj", "./Assets/Textures/Floor.png", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/FloorNormal.png");
	texturedObjects.push_back(mOb);

	mOb = new CTexturedObject("./Assets/Models/pared1-brick.obj", "./Assets/Textures/brick.jpg", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/brick-normal.jpg");
	texturedObjects.push_back(mOb);
	
	mOb = new CTexturedObject("./Assets/Models/pared2-brick.obj", "./Assets/Textures/brick.jpg", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/brick-normal.jpg");
	texturedObjects.push_back(mOb);

	mOb = new CTexturedObject("./Assets/Models/pared3-brick.obj", "./Assets/Textures/brick.jpg", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/brick-normal.jpg");
	texturedObjects.push_back(mOb);

	mOb = new CTexturedObject("./Assets/Models/pared4-brick.obj", "./Assets/Textures/brick.jpg", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/brick-normal.jpg");
	texturedObjects.push_back(mOb);

	mOb = new CTexturedObject("./Assets/Models/techo-brick.obj", "./Assets/Textures/brick.jpg", NORMAL);
	mOb->getTexture()->loadTexture("./Assets/Textures/brick-normal.jpg");
	texturedObjects.push_back(mOb);

	mOb = new CTexturedObject("./Assets/Models/cubo1.obj", "./Assets/Textures/rock_diffuse.bmp", PARALLAX);
	mOb->getTexture()->loadTexture("./Assets/Textures/rock_height.bmp");
	texturedObjects.push_back(mOb);
	
	mOb = new CTexturedObject("./Assets/Models/cubo2.obj", "./Assets/Textures/rock_diffuse.bmp", PARALLAX);
	mOb->getTexture()->loadTexture("./Assets/Textures/rock_height.bmp");
	texturedObjects.push_back(mOb);

	CObject* mOb2 = new CObject("./Assets/Models/espejo.obj");
	//mOb->getTexture()->loadTexture("./Assets/Textures/rock_height.bmp");
	objects.push_back(mOb2);
	
	/*mOb = new CTexturedObject("./Assets/Models/cubo2.obj", "./Assets/Textures/rock_diffuse.jpg", PARALLAX);
	mOb->getTexture()->loadTexture("./Assets/Textures/rock_height.jpg");
	texturedObjects.push_back(mOb);
*/
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

	//Normal---------------------------------------------------------------------------------------------------
	//Load the shaders
	normal_program.loadShader("./Assets/shaders/basic.vert", CGLSLProgram::VERTEX);
	//normal_program.loadShader("./Assets/shaders/Normal Mapping.frag", CGLSLProgram::FRAGMENT);
	normal_program.loadShader("./Assets/shaders/Normal Mapping.frag", CGLSLProgram::FRAGMENT);
	//Link the shaders in a program
	normal_program.create_link();
	//Enable the program
	normal_program.enable();
	//Link the attributes and the uniforms
	normal_program.addAttribute("vVertex");
	normal_program.addAttribute("vColor");
	normal_program.addAttribute("vNormal");
	normal_program.addAttribute("vTexture");
	normal_program.addAttribute("vTangent");
	normal_program.addAttribute("vBitangent");
	normal_program.addUniform("mProjection");
	normal_program.addUniform("mModelView");

	normal_program.addUniform("centerPosition");
	normal_program.addUniform("translateFactor");
	normal_program.addUniform("scaleFactor");
	normal_program.addUniform("quat");

	normal_program.addUniform("lightIndex");
	normal_program.addUniform("ambient");
	normal_program.addUniform("diffuse");
	normal_program.addUniform("specular");
	normal_program.addUniform("position");

	for (int i = 0; i < 2; i++){
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].type");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].ambient");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].diffuse");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].specular");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].position");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].shininness");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].constantAttenuation");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].linearAttenuation");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].quadraticAttenuation");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].spotDirection");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].spotExponent");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCutoff");
		normal_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCosCutoff");
	}

	normal_program.addUniform("eyePos");

	normal_program.addUniform("diffuseObject");
	normal_program.addUniform("specularObject");
	normal_program.addUniform("ambientObject");
	normal_program.addUniform("sceneAmbient");
	//Constantes del modelo cook torrance
	normal_program.addUniform("roughnessValue");
	normal_program.addUniform("fresnelValue");
	normal_program.addUniform("gaussConstant");
	//Texturas
	normal_program.addUniform("textureSampler");
	normal_program.addUniform("normalSampler");
	//Disable the program
	normal_program.disable();

	//Parallax-------------------------------
	//Load the shaders
	parallax_program.loadShader("./Assets/shaders/basic.vert", CGLSLProgram::VERTEX);
	//parallax_program.loadShader("./Assets/shaders/Normal Mapping.frag", CGLSLProgram::FRAGMENT);
	parallax_program.loadShader("./Assets/shaders/parallaxMapping.frag", CGLSLProgram::FRAGMENT);
	//Link the shaders in a program
	parallax_program.create_link();
	//Enable the program
	parallax_program.enable();
	//Link the attributes and the uniforms
	parallax_program.addAttribute("vVertex");
	parallax_program.addAttribute("vColor");
	parallax_program.addAttribute("vNormal");
	parallax_program.addAttribute("vTexture");
	parallax_program.addAttribute("vTangent");
	parallax_program.addAttribute("vBitangent");
	parallax_program.addUniform("mProjection");
	parallax_program.addUniform("mModelView");

	parallax_program.addUniform("centerPosition");
	parallax_program.addUniform("translateFactor");
	parallax_program.addUniform("scaleFactor");
	parallax_program.addUniform("quat");

	parallax_program.addUniform("lightIndex");
	parallax_program.addUniform("ambient");
	parallax_program.addUniform("diffuse");
	parallax_program.addUniform("specular");
	parallax_program.addUniform("position");

	for (int i = 0; i < 2; i++){
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].type");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].ambient");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].diffuse");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].specular");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].position");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].shininness");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].constantAttenuation");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].linearAttenuation");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].quadraticAttenuation");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].spotDirection");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].spotExponent");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCutoff");
		parallax_program.addUniform("lightParameters[" + std::to_string(i) + "].spotCosCutoff");
	}

	parallax_program.addUniform("eyePos");

	parallax_program.addUniform("diffuseObject");
	parallax_program.addUniform("specularObject");
	parallax_program.addUniform("ambientObject");
	parallax_program.addUniform("sceneAmbient");
	//Constantes del modelo cook torrance
	parallax_program.addUniform("roughnessValue");
	parallax_program.addUniform("fresnelValue");
	parallax_program.addUniform("gaussConstant");
	//Texturas
	parallax_program.addUniform("textureSampler");
	parallax_program.addUniform("normalSampler");
	//Disable the program
	parallax_program.disable();
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
	programs.push_back(&normal_program);
	programs.push_back(&parallax_program);
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