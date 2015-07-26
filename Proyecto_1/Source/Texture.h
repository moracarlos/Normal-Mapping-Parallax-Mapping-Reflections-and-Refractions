#pragma once

#include "glm\glm.hpp"
#include "Main.h"
#include <iostream>

enum textureType
{
	NONE,
	NORMAL,
	PARALLAX,
	CUBEMAP
};

class CTexture{
private:
	int nTextures;
	int imageWidth, imageHeight, imageFormat, id;
	GLuint mTextures[3];
	std::vector<float> mTextureCoord;
	textureType mType;
public:
	CTexture(const char* file, textureType mType);
	CTexture(const char* posx, const char*  negx, const char* posy, const char* negy, const char* posz, const char* negz, textureType mType);
	unsigned int loadTexture(const char* filename);

	GLuint getTextureID(int i);
	void enable();
	void disable();
	textureType getType();
	void setType(textureType mType);
};