#pragma once

#include <cstdio>
#include <glm\glm.hpp>
#include <gl/glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IL\il.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "GLSLProgram.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void display();

void reshape(GLFWwindow *window, int iWidth, int iHeight);

void refresh(int picked);

void gluperspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

void keyInput(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, static unsigned int scanChar);

bool initialize();

void errorCB(int error, const char* description);

void destroy();

bool initGLFW();

bool initUserInterface();

void setUserInterface();

void updateUserInterface();

void mainLoop();

int main(void);

