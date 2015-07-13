#pragma once

#include "glm\glm.hpp"
#include "Main.h"
#include <iostream>

class CTexture{
private:
	int nTextures;
	int imageWidth, imageHeight, imageFormat, id;
	GLuint mTextures[3];
	std::vector<float> mTextureCoord;
public:
	CTexture(const char* file);
	unsigned int loadTexture(const char* filename);

	GLuint getTextureID(int i);
	void enable();
	void disable();
};