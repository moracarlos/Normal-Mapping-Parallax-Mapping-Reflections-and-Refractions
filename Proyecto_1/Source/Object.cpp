#include "Object.h"
#include "Scene.h"

extern CScene* gpScene;

CObject::CObject(std::string path){
	nVertex = 0;
	nFaces = 0;
	nEdges = 0;
	nIndex = 0;
	current_shader = 0;
	mIndexes.clear();
	mVertex.clear();
	mFaceNormals.clear();
	mVertexNormals.clear();
	mColor.clear();
	xmin = ymin = zmin = xmax = ymax = zmax = NULL;
	transFX = transFY = transFZ = 0;
	scaleFX = scaleFY = scaleFZ = 1;
	ambientObject[0] = ambientObject[1] = ambientObject[2] = 0.5;
	diffuseObject[0] = diffuseObject[1] = diffuseObject[2] = 0.5;
	specularObject[0] = specularObject[1] = specularObject[2] = 1;
	roughnessValue = 1.0; 
	fresnelValue = 0.10; 
	gaussConstant = 100;
	quat[0] = quat[1] = quat[2] = quat[3] = 0;
	yaw = 0.f;
	loadObject(path);
	initBuffers();
}

int CObject::loadObject(std::string path){

	std::fstream file(path, std::fstream::in | std::fstream::out);
	if (!file.is_open()){
		std::cout << "No se pudo abrir el archivo" << std::endl; 
		return 0;
	}
		int i, j, indexMinMax = 0, numF;
		GLfloat point;
		std::vector <GLuint> fc,ft;
		GLuint pt;
		std::string type;
		file >> type;
		j = 0;
		fc.clear();
		while (!file.eof()){
			std::string subtype = type.substr(0, 1);
			std::string line;
			if (subtype == "#"){
				std::getline(file, line);
			}
			if (type == "vt"){
				std::getline(file, line);
			}
			if (type == "vn"){
				std::getline(file, line);
			} //List of Vertex
			if (type == "v"){
				for (i = 0; i < 3; i++){
					file >> point;
					mVertex.push_back(point);
					switch (i){
					case 0:
						if (xmin == NULL){
							xmin = point;
						}
						else{
							if (point < xmin) xmin = point;
						}
						if (xmax == NULL){
							xmax = point;
						}
						else{
							if (point > xmax) xmax = point;
						}
						break;
					case 1:
						if (ymin == NULL){
							ymin = point;
						}
						else{
							if (point < ymin) ymin = point;
						}
						if (ymax == NULL){
							ymax = point;
						}
						else{
							if (point > ymax) ymax = point;
						}
						break;
					case 2:
						if (zmin == NULL){
							zmin = point;
						}
						else{
							if (point < zmin) zmin = point;
						}
						if (zmax == NULL){
							zmax = point;
						}
						else{
							if (point > zmax) zmax = point;
						}
						break;
					}

				}
				mColor.push_back(0);
				mColor.push_back(1);
				mColor.push_back(0);
				nVertex++;
				//
				//calculateMinMax(indexMinMax);
				indexMinMax++;
				//
				}//List of Faces
				if (type == "f"){
					std::getline(file, line);
					char * tok = strtok(&line[0u], " ");
					while (tok != NULL){
						std::string num = tok;
						std::size_t pos = num.find("/");
						num = num.substr(0, pos);
						pt = stoi(num);
						fc.push_back(pt);
						tok = strtok(NULL, " ");
					}
					nFaces++;
					for (j = 1; j < fc.size() - 1; j++){
						mIndexes.push_back(fc[0] - 1);
						mIndexes.push_back(fc[j] - 1);
						mIndexes.push_back(fc[j + 1] - 1);
					}
					fc.clear();
				}
				file >> type;
			}

		xmid = (xmin + xmax) / 2;
		ymid = (ymin + ymax) / 2;
		zmid = (zmin + zmax) / 2;

		calculateFaceNormals();
		calculateVertexNormals();

		//Initialize buffer

		file.close();
		std::cout << "Object loaded" << std::endl;
		return 1;
}

void CObject::calculateFaceNormals(){
	float alpha = 0.1f;
	int i, j;
	glm::vec3 v1, v2, c, p1, p2, p3, n;
	for (i = 0; i < mIndexes.size(); i += 3){
		p1 = glm::vec3(mVertex[mIndexes[i] * 3], mVertex[mIndexes[i] * 3 + 1], mVertex[mIndexes[i] * 3 + 2]);
		p2 = glm::vec3(mVertex[mIndexes[i + 1] * 3], mVertex[mIndexes[i + 1] * 3 + 1], mVertex[mIndexes[i + 1] * 3 + 2]);
		p3 = glm::vec3(mVertex[mIndexes[i + 2] * 3], mVertex[mIndexes[i + 2] * 3 + 1], mVertex[mIndexes[i + 2] * 3 + 2]);
		v1 = glm::normalize(p2 - p1);
		v2 = glm::normalize(p3 - p1);
		c = (p1 + p2 + p3) / 3.f;
		n = glm::normalize(glm::cross(v1, v2)); //Aqui esta el cambio

		mFaceNormals.push_back(c[0]);
		mFaceNormals.push_back(c[1]);
		mFaceNormals.push_back(c[2]);

		mFaceNormals.push_back(n[0]);
		mFaceNormals.push_back(n[1]);
		mFaceNormals.push_back(n[2]);
	}
}

void CObject::calculateVertexNormals(){
	int i, j = 0;
	mVertexNormals.clear();
	for (i = 0; i < mVertex.size(); i++){
		mVertexNormals.push_back(0);
	}

	for (i = 0; i < mIndexes.size(); i += 3){
		float x = mFaceNormals[2 * i + 3], y = mFaceNormals[2 * i + 4], z = mFaceNormals[2 * i + 5];

		mVertexNormals[mIndexes[i] * 3] += x;
		mVertexNormals[mIndexes[i] * 3 + 1] += y;
		mVertexNormals[mIndexes[i] * 3 + 2] += z;

		mVertexNormals[mIndexes[i + 1] * 3] += x;
		mVertexNormals[mIndexes[i + 1] * 3 + 1] += y;
		mVertexNormals[mIndexes[i + 1] * 3 + 2] += z;

		mVertexNormals[mIndexes[i + 2] * 3] += x;
		mVertexNormals[mIndexes[i + 2] * 3 + 1] += y;
		mVertexNormals[mIndexes[i + 2] * 3 + 2] += z;
	}

	glm::vec3 n;
	float alpha = 0.1f;
	for (i = 0; i < mVertexNormals.size(); i += 3){
		n = glm::vec3(mVertexNormals[i], mVertexNormals[i + 1], mVertexNormals[i + 2]);
		n = glm::normalize(n);

		mVertexNormals[i] = n[0];
		mVertexNormals[i + 1] = n[1];
		mVertexNormals[i + 2] = n[2];
	}
}

std::vector <GLfloat> CObject::getVertexes()
{
	return mVertex;
}

std::vector <GLfloat> CObject::getVertexNormals()
{
	return mVertexNormals;
}

std::vector <GLfloat> CObject::getColors()
{
	return mColor;
}

std::vector <GLuint> CObject::getIndexes()
{
	return mIndexes;
}

float CObject::getRoughnessValue(){
	return roughnessValue;
}

float CObject::getFresnelValue(){
	return fresnelValue;
}

float CObject::getGaussConstant(){
	return gaussConstant;
}

GLuint CObject::getCurrentShader(){
	return current_shader;
}

void CObject::setCurrentShader(GLuint c){
	current_shader = c;
}

void CObject::setRoughnessValue(float r){
	roughnessValue = r;
}

void CObject::setFresnelValue(float f){
	fresnelValue = f;
}

void CObject::setGaussConstant(float g){
	gaussConstant = g;
}

void CObject::setAmbientObject(glm::vec3 ambient){
	ambientObject = ambient;
}

void CObject::setDiffuseObject(glm::vec3 diffuse){
	diffuseObject = diffuse;
}

void CObject::setSpecularObject(glm::vec3 specular){
	specularObject = specular;
}

glm::vec3 CObject::getAmbientObject(){
	return ambientObject;
}

glm::vec3 CObject::getDiffuseObject(){
	return diffuseObject;
}

glm::vec3 CObject::getSpecularObject(){
	return specularObject;
}

bool CObject::initBuffers()
{
	//Generate the Vertex Array
	glGenVertexArrays(1, &m_idVAO);
	glBindVertexArray(m_idVAO);

	//Generate the buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vindex);

	//Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Allocate space for the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mVertex.size() + sizeof(float)*mColor.size() + sizeof(float)*mVertexNormals.size(), NULL, GL_DYNAMIC_DRAW);
	//Pass the vertex and the color data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*mVertex.size(), mVertex.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*mVertex.size(), sizeof(float)*mColor.size(), mColor.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*mColor.size() + sizeof(float)*mVertex.size(), sizeof(float)*mVertexNormals.size(), mVertexNormals.data());

	glEnableVertexAttribArray(gpScene->getProgram()[current_shader]->getLocation("vVertex"));
	glVertexAttribPointer(gpScene->getProgram()[current_shader]->getLocation("vVertex"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //Vertex
	glEnableVertexAttribArray(gpScene->getProgram()[current_shader]->getLocation("vColor"));
	glVertexAttribPointer(gpScene->getProgram()[current_shader]->getLocation("vColor"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(mVertex.size()*sizeof(float))); //Colors
	glEnableVertexAttribArray(gpScene->getProgram()[current_shader]->getLocation("vNormal"));
	glVertexAttribPointer(gpScene->getProgram()[current_shader]->getLocation("vNormal"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(mVertex.size()*sizeof(float) + mColor.size()*sizeof(float))); //Normals

	//Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	//Fill the index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mIndexes.size(), mIndexes.data(), GL_STATIC_DRAW);

	//Unbind Vertex Array
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

void CObject::display(){
	std::stringstream ss;
	std::string uniformName;

	programs = gpScene->getProgram();

	if (current_shader == 2) //Si esta habilitado el shader de toon
	{
		glCullFace(GL_FRONT);

		programs[3]->enable(); //Habilitamos el shader para la silueta;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);

		glUniformMatrix4fv(programs[current_shader]->getLocation("mModelView"), 1, GL_FALSE, glm::value_ptr(gpScene->getModelViewMatrix()));
		glUniformMatrix4fv(programs[current_shader]->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(gpScene->getProjectionMatrix()));
		glUniform3f(programs[current_shader]->getLocation("scaleFactor"), scaleFX+0.02, scaleFY+0.02, scaleFZ+0.02);
		glUniform3f(programs[current_shader]->getLocation("translateFactor"), transFX, transFY, transFZ);
		glUniform4f(programs[current_shader]->getLocation("quat"), quat[0], quat[1], quat[2], quat[3]);
		glUniform3f(programs[current_shader]->getLocation("centerPosition"), (xmin + xmax) / 2, (ymin + ymax) / 2, (zmin + zmax) / 2);

		glBindVertexArray(m_idVAO);

		//glPolygonMode(GL_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, sizeof(GLuint)*mIndexes.size(), GL_UNSIGNED_INT, NULL);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		programs[3]->disable();
		
		glCullFace(GL_BACK);
	}
	

	programs[current_shader]->enable(); //glUseProgram;
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);

	glUniformMatrix4fv(programs[current_shader]->getLocation("mModelView"), 1, GL_FALSE, glm::value_ptr(gpScene->getModelViewMatrix()));
	glUniformMatrix4fv(programs[current_shader]->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(gpScene->getProjectionMatrix()));
	glUniform3f(programs[current_shader]->getLocation("scaleFactor"), scaleFX, scaleFY, scaleFZ);
	glUniform3f(programs[current_shader]->getLocation("translateFactor"), transFX, transFY, transFZ);
	glUniform4f(programs[current_shader]->getLocation("quat"), quat[0], quat[1], quat[2], quat[3]);
	glUniform3f(programs[current_shader]->getLocation("centerPosition"), (xmin + xmax) / 2, (ymin + ymax) / 2, (zmin + zmax) / 2);

	for (int i = 0; i < 3; i++){
		glUniform1i(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].type"), gpScene->getLights()[i].type);
		glUniform3fv(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].ambient"), 1, glm::value_ptr(gpScene->getLights()[i].ambient));
		glUniform3fv(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].diffuse"), 1, glm::value_ptr(gpScene->getLights()[i].diffuse));
		glUniform3fv(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].specular"), 1, glm::value_ptr(gpScene->getLights()[i].specular));
		glUniform3fv(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].position"), 1, glm::value_ptr(gpScene->getLights()[i].position));
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].constantAttenuation"), gpScene->getLights()[i].constantAttenuation);
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].linearAttenuation"), gpScene->getLights()[i].linearAttenuation);
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].quadraticAttenuation"), gpScene->getLights()[i].quadraticAttenuation);
		glUniform3fv(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].spotDirection"), 1, glm::value_ptr(gpScene->getLights()[i].spotDirection));
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].spotExponent"), gpScene->getLights()[i].spotExponent);
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].spotCutoff"), gpScene->getLights()[i].spotCutoff);
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].spotCosCutoff"), gpScene->getLights()[i].spotCosCutoff);
		glUniform1f(programs[current_shader]->getLocation("lightParameters[" + std::to_string(i) + "].shininness"), gpScene->getLights()[i].shininness);
	}
	glUniform3fv(programs[current_shader]->getLocation("eyePos"), 1, glm::value_ptr(gpScene->getEyePos()));
	glUniform3fv(programs[current_shader]->getLocation("diffuseObject"), 1, glm::value_ptr(diffuseObject));
	glUniform3fv(programs[current_shader]->getLocation("specularObject"), 1, glm::value_ptr(specularObject));
	glUniform3fv(programs[current_shader]->getLocation("ambientObject"), 1, glm::value_ptr(ambientObject));
	glUniform3fv(programs[current_shader]->getLocation("sceneAmbient"), 1, glm::value_ptr(gpScene->getAmbient()));

	glUniform1f(programs[current_shader]->getLocation("roughnessValue"), roughnessValue);
	glUniform1f(programs[current_shader]->getLocation("fresnelValue"), fresnelValue);
	glUniform1f(programs[current_shader]->getLocation("gaussConstant"), gaussConstant);

	glBindVertexArray(m_idVAO);
	glDrawElements(GL_TRIANGLES, sizeof(GLuint)*mIndexes.size(), GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	programs[current_shader]->disable();

}

void CObject::displaySelection(int i)
{
	programs = gpScene->getProgram();

	/*programs[4]->enable(); //glUseProgram;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);

	glUniformMatrix4fv(programs[4]->getLocation("mModelView"), 1, GL_FALSE, glm::value_ptr(gpScene->getModelViewMatrix()));
	glUniformMatrix4fv(programs[4]->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(gpScene->getProjectionMatrix()));
	glUniform3f(programs[4]->getLocation("scaleFactor"), scaleFX, scaleFY, scaleFZ);
	glUniform3f(programs[4]->getLocation("translateFactor"), transFX, transFY, transFZ);
	glUniform4f(programs[4]->getLocation("quat"), quat[0], quat[1], quat[2], quat[3]);
	glUniform3f(programs[4]->getLocation("centerPosition"), (xmin + xmax) / 2, (ymin + ymax) / 2, (zmin + zmax) / 2);
	glUniform1i(programs[4]->getLocation("code"), i);

	glBindVertexArray(m_idVAO);
	glDrawElements(GL_TRIANGLES, sizeof(GLuint)*mIndexes.size(), GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	programs[4]->disable();
	*/

}

void CObject::incrementYaw(float val)
{
	yaw += val;
	glm::quat myQuat(glm::vec3(0.f, yaw, 0.f));
	quat[0] = myQuat.x;
	quat[1] = myQuat.y;
	quat[2] = myQuat.z;
	quat[3] = myQuat.w;
}

void CObject::setTransFX(float val)
{
	transFX = val;
}
void CObject::setTransFY(float val)
{
	transFY = val;
}
void CObject::setTransFZ(float val)
{
	transFZ = val;
}