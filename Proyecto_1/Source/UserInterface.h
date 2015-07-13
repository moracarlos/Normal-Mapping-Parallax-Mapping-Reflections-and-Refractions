#pragma once

#include <AntTweakBar\AntTweakBar.h>
#include "Object.h"
#include "Scene.h"

class CUserInterface{
private:
	GLfloat mFigureColor[3], factorX, factorY, factorZ, quat[4], trasX, trasY, trasZ;
	int indexObj;
	bool test;
	TwBar *mBar;
	lightParameters mLights[3];
	GLfloat diffuseObject[3], specularObject[3], ambientObject[3], sceneAmbient[3], roughnessValue, fresnelValue, gaussConstant;

public:
	CUserInterface();
	~CUserInterface();
	void reshape();
	void setFigureColor(GLfloat r, GLfloat g, GLfloat b);
	GLfloat* getFigureColor();
	void setFactorX(float fc);
	GLfloat getFactorX();
	void setFactorY(float fc);
	GLfloat getFactorY();
	void setFactorZ(float fc);
	GLfloat getFactorZ();
	void setTrasX(float fc);
	GLfloat getTrasX();
	void setTrasY(float fc);
	GLfloat getTrasY();
	void setTrasZ(float fc);
	GLfloat getTrasZ();
	float* getAmbientObject();
	float* getDiffuseObject();
	float* getSpecularObject();
	void setAmbientObject(float r, float g, float b);
	void setDiffuseObject(float r, float g, float b);
	void setSpecularObject(float r, float g, float b);
};
