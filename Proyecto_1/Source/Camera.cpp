#include "Camera.h"
#include "Scene.h"

extern GLFWwindow* gpWindow;
extern CScene* gpScene;
extern int gWidth;
extern int gHeight;
extern double timeElapsed;

CCamera::CCamera(){
	yaw = 270.f;
	pitch = 0.f;
	leftButtonPress = false;
	cameraPos = glm::vec3(0.f, 0.f, 10.f);
	cameraFront = glm::vec3(0.f, 0.f, -1.f);
	cameraUp = glm::vec3(0.f, 1.f, 0.f);
	for (int i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
	deltaTime = 0.f;
	lastFrame = 0.f;
	currentFrame = 0.f;
}

glm::vec3 CCamera::getPosition()
{
	return cameraPos;
}

glm::vec3 CCamera::getUp()
{
	return cameraUp;
}

glm::vec3 CCamera::getFront()
{
	return cameraFront;
}

void CCamera::moveCamera()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed*cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed *cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	gpScene->setEyePos(cameraPos);
}

void CCamera::setLeftButtonPress(bool val, float x, float y)
{
	leftButtonPress = val;
	if (val){
		lastX = x;
		lastY = y;
	}
}

void CCamera::handleCursorPos(double x, double y)
{
	if (leftButtonPress){
	//	std::cout << yaw << std::endl;
		float horizMouseMovement = ((float)x - lastX) * 0.15;
		float vertMouseMovement = (lastY - (float)y) * 0.15;
		lastX = x;
		lastY = y;

		pitch += -vertMouseMovement;//X axis
		yaw += horizMouseMovement;

		if (pitch < -89.0) pitch = -89.f;
		if (pitch > 89.0) pitch = 89.0;

		if (yaw > 359.9f) yaw = 0.f;
		if (yaw < 0.f) yaw = 359.f;

		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}

void CCamera::setKeyPress(int key, bool val)
{
	keys[key] = val;
}