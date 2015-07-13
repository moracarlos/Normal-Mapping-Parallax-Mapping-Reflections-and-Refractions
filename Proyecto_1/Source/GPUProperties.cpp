#include "GPUProperties.h"

// <-- Constructor --> //

CGPUProperties::CGPUProperties(){

	mVendor = reinterpret_cast<const GLchar*>(glGetString(GL_VENDOR));
	mRenderer = reinterpret_cast<const GLchar*>(glGetString(GL_RENDERER));
	mOpenGLVersion = reinterpret_cast<const GLchar*>(glGetString(GL_VERSION));
	mGLSLVersion = reinterpret_cast<const GLchar*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

}

// <-- Destructor --> //

CGPUProperties::~CGPUProperties(){

}

// <-- Gets vendor --> //

string CGPUProperties::getVendor(){

	return mVendor;

}

// <-- Gets renderer --> //

string CGPUProperties::getRenderer(){

	return mRenderer;

}

// <-- Gets GLSL version --> //

string CGPUProperties::getGLSLVersion(){

	return mGLSLVersion;

}

// <-- Gets OpenGL version --> //

string CGPUProperties::getOpenGLVersion(){

	return mOpenGLVersion;

}