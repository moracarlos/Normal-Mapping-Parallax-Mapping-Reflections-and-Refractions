#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Main.h"

class CObject{
private:
	GLuint vbo, vindex, m_idVAO, current_shader;
	int nVertex, nFaces, nEdges, nIndex;
	std::vector <GLuint> mIndexes;
	std::vector <GLfloat> mVertex, mFaceNormals, mVertexNormals, mColor;
	std::vector <CGLSLProgram*> programs;
	GLfloat quat[4];
	GLfloat xmin, ymin, zmin, xmax, ymax, zmax, xmid, ymid, zmid;
	GLfloat transFX, transFY, transFZ, scaleFX, scaleFY, scaleFZ;
	glm::vec3 ambientObject, diffuseObject, specularObject;
	float roughnessValue, fresnelValue, gaussConstant;
	float yaw;

public:
	CObject(std::string path);
	~CObject();
	bool initBuffers();
	void display();
	void displaySelection(int i);
	int initialize();
	int loadObject(std::string path);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	GLfloat* getColor();
	void calculateFaceNormals();
	void calculateVertexNormals();
	glm::vec3 getAmbientObject();
	glm::vec3 getDiffuseObject();
	glm::vec3 getSpecularObject();
	float getRoughnessValue();
	float getFresnelValue();
	float getGaussConstant();
	GLuint getCurrentShader();
	void setCurrentShader(GLuint c);
	void setAmbientObject(glm::vec3 ambient);
	void setDiffuseObject(glm::vec3 diffuse);
	void setSpecularObject(glm::vec3 specular);
	void setRoughnessValue(float r);
	void setFresnelValue(float f);
	void setGaussConstant(float g);
	std::vector <GLfloat> getVertexes();
	std::vector <GLfloat> getVertexNormals();
	std::vector <GLfloat> getColors();
	std::vector <GLuint> getIndexes();
	void incrementYaw(float val);
	void setTransFX(float val);
	void setTransFY(float val);
	void setTransFZ(float val);
};