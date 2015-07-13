#pragma once

#include "glm\glm.hpp"
#include "Main.h"
#include <iostream>

class CCamera{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::vec3 front;
	float yaw;
	float pitch;
	float cameraSpeed;
	bool keys[1024];
	bool leftButtonPress;
	float deltaTime;
	float lastFrame;
	float currentFrame;
	float lastX;
	float lastY;

public:
	CCamera();
	void moveCamera();

	glm::vec3 getPosition();
	glm::vec3 getUp();
	glm::vec3 getFront();

	void setKeyPress(int key, bool val);
	void setLeftButtonPress(bool val, float x, float y);
	void handleCursorPos(double x, double y);
};