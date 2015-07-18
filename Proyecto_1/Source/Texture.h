#pragma once

#include "glm\glm.hpp"
#include "Main.h"
#include <iostream>

enum textureType
{
	NONE,
	NORMAL,
	PARALLAX
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
	unsigned int loadTexture(const char* filename);

	GLuint getTextureID(int i);
	void enable();
	void disable();
	textureType getType();
	void setType(textureType mType);
};