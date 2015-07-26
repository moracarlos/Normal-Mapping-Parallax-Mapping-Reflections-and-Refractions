#include "Texture.h"

CTexture::CTexture(const char* file, textureType mType)
{
	nTextures = 0;
	loadTexture(file);
	this->mType = mType;
}

CTexture::CTexture(const char* posx, const char*  negx, const char* posy, const char* negy, const char* posz, const char* negz, textureType mType)
{
	nTextures = 0;
	this->mType = mType;
	ilInit();
	ILuint imageID;
	ILboolean success;
	ILenum error;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	
		
		glGenTextures(1, &mTextures[nTextures]);
		glActiveTexture(mTextures[nTextures]);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mTextures[nTextures]);

		for (GLuint i = 0; i < 6; i++)
		{
			switch (i){
			case 0:
				success = ilLoadImage(posx);
				break;
			case 1:
				success = ilLoadImage(negx);
				break;
			case 2:
				success = ilLoadImage(posy);
				break;
			case 3:
				success = ilLoadImage(negy);
				break;
			case 4:
				success = ilLoadImage(posz);
				break;
			case 5:
				success = ilLoadImage(negz);
				break;
			}
			success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
			if (!success){
				error = ilGetError();
				std::cout << "Image conversion fails" << std::endl;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),
				0,
				ilGetInteger(IL_IMAGE_FORMAT),
				GL_UNSIGNED_BYTE,
				ilGetData()
				);

		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		
		
		ilDeleteImages(1, &imageID);
		std::cout << "Textura creada exitosamente" << std::endl;
		nTextures++;
}


GLuint CTexture::getTextureID(int i)
{
	return mTextures[i];
}

unsigned int CTexture::loadTexture(const char* file)
{
	ilInit();
	ILuint imageID;
	ILboolean success;
	ILenum error;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	success = ilLoadImage(file);
	if (success)
	{
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!success){
			error = ilGetError();
			std::cout << "Image conversion fails" << std::endl;
		}
		glGenTextures(1, &mTextures[nTextures]);
		glBindTexture(GL_TEXTURE_2D, mTextures[nTextures]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			GL_UNSIGNED_BYTE,
			ilGetData()
			);
		imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
		imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
		imageFormat = ilGetInteger(IL_IMAGE_FORMAT);
	}

	ilDeleteImages(1, &imageID);
	std::cout << "Textura creada exitosamente" << std::endl;
	nTextures++;
	return 0;
}

void CTexture::enable()
{
	if (mType == CUBEMAP){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mTextures[0]);
	}
	else{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTextures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mTextures[1]);
	}
	//for (int i = 0; i < nTextures; i++){
		//glBindTexture(GL_TEXTURE_2D, mTextures[i]);
	//}
}

void CTexture::disable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

textureType CTexture::getType()
{
	return mType;
}

void CTexture::setType(textureType mType)
{
	this->mType = mType;
}