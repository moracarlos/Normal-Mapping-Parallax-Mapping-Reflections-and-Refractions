#include "Main.h"
#include "UserInterface.h"
#include "Scene.h"
#include "Camera.h"

int gWidth;
int gHeight;
GLFWwindow* gpWindow;
const float fAngle = 45.0;
float ratio;
const float NCP = 0.01f;
const float FCP = 200.0f;
CUserInterface *gpUserInterface;
CScene* gpScene;
CCamera* gpCamera;
int picked=0;

int main(){
	gWidth = 1024;
	gHeight = 600;

	if (!initGLFW() || !initUserInterface())
		return EXIT_FAILURE;

	if (!initialize())
		exit(EXIT_FAILURE);

	gpScene = new CScene();

	gpCamera = new CCamera();

	gpScene->loadObjects();

	reshape(gpWindow, gWidth, gHeight);
	
	mainLoop();

	destroy();
	return EXIT_SUCCESS;
}

bool initUserInterface(){
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	gpUserInterface = new CUserInterface();

	return true;
}

bool initGLFW()
{
	glfwSetErrorCallback(errorCB);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	gpWindow = glfwCreateWindow(gWidth, gHeight, "Computer Graphics", NULL, NULL);
	if (!gpWindow){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gpWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwMakeContextCurrent(gpWindow);

	glfwSetKeyCallback(gpWindow, keyInput);
	glfwSetWindowSizeCallback(gpWindow, reshape);
	glfwSetMouseButtonCallback(gpWindow, mouseButton);
	glfwSetCursorPosCallback(gpWindow, cursorPos);
	glfwSetCharCallback(gpWindow, charInput);

	return true;
}

void keyInput(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods){
	if (iAction == GLFW_PRESS){
		switch (iKey){
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			gpCamera->setKeyPress(iKey, true);
		}
	}
	else if (iAction == GLFW_RELEASE){
		gpCamera->setKeyPress(iKey, false);
	}
}

void processSelection(int xx, int yy)
{
	if (xx > 240){
		unsigned char res[4];
		GLint viewport[4];

		glFrontFace(GL_CCW);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		std::vector<CObject*> mObjects = gpScene->getObjects();

		reshape(gpWindow, gWidth, gHeight);

		gpScene->setProjectionMatrix(gpScene->getProjectionMatrix() * glm::lookAt(gpCamera->getPosition(), gpCamera->getPosition() + gpCamera->getFront(), gpCamera->getUp()));

		for (int i = 0; i < mObjects.size(); i++){
			mObjects[i]->displaySelection(i);
		}


		glGetIntegerv(GL_VIEWPORT, viewport);
		glReadPixels(xx, viewport[3] - yy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

		int pickedID =
			res[0] +
			res[1] * 256 +
			res[2] * 256 * 256;
		std::cout << pickedID << std::endl;
		switch (pickedID)
		{
		case 3355443:
			picked = 0;
			break;
		case 5000268:
			picked = 1;
			break;
		case 6710886:
			picked = 2;
			break;
		case 8421504:
			picked = 3;
			break;
		default:
			break;
		}

	}

}

void mouseButton(GLFWwindow* window, int button, int action, int mods){
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gpWindow, &x, &y);
	float ax = x;
	float ay = gHeight - y;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		gpCamera->setLeftButtonPress(true, x,y);
		processSelection(x, y);
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		gpCamera->setLeftButtonPress(false, x, y);
	}
}

void cursorPos(GLFWwindow* window, double x, double y){
	if (TwEventMousePosGLFW(x, y))
		return;

	float ax = x;
	float ay = gHeight - y;

	gpCamera->handleCursorPos(x, y);

}

void charInput(GLFWwindow* window, static unsigned int scanChar){
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void errorCB(int error, const char* description){
	std::cout << description << std::endl;
}

void destroy(){
	int i;

	glfwDestroyWindow(gpWindow);
	glfwTerminate();
}

bool initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Glew INIT
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "- glew Init failed :(" << std::endl;
		//return false;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	return true;
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;
	gpUserInterface->reshape();
	ratio = gWidth / float(gHeight);
	if (gHeight == 0) gHeight = 1;
	glViewport(0, 0, gWidth, gHeight);
	gluperspective(fAngle, ratio, NCP, FCP);

	//Nueva posicion de la camra
	gpScene->setProjectionMatrix(gpScene->getProjectionMatrix() * glm::lookAt(gpCamera->getPosition(), gpCamera->getPosition()+gpCamera->getFront(), gpCamera->getUp()));
}

void gluperspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	fH = tan(fovY / 360 * pi) * zNear;	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
	gpScene->setProjectionMatrix(glm::frustum(-fW, fW, -fH, fH, zNear, zFar));
}

void mainLoop()
{
	while (!glfwWindowShouldClose(gpWindow)){
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gpWindow);

		glfwPollEvents();

		gpCamera->moveCamera();
	}
}

void updateUserInterface()
{

}

void display()
{
	glFrontFace(GL_CCW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	std::vector<CObject*> mObjects = gpScene->getObjects();
	std::vector<CTexturedObject*> mTexturedObjects = gpScene->getTexturedObjects();
	std::vector<CTexturedObject*> mMirrors = gpScene->getMirrors();

	//Se dibujan los espejos
	reshape(gpWindow, gWidth, gHeight);
	gpScene->setProjectionMatrix(gpScene->getProjectionMatrix() * glm::lookAt(gpCamera->getPosition(), gpCamera->getPosition() + gpCamera->getFront(), gpCamera->getUp()));

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_NEVER, 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);  // draw 1s on test fail (always)

	// draw stencil pattern
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);  // needs mask=0xFF
	for (int i = 0; i < mMirrors.size(); i++){
		mMirrors[i]->display();
	}

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0x00);
	// draw where stencil's value is 0
	glStencilFunc(GL_EQUAL, 0, 0xFF);
	/* (nothing to draw) */
	// draw only where stencil's value is 1
	glStencilFunc(GL_EQUAL, 1, 0xFF);

	glFrontFace(GL_CW);

	for (int i = 0; i < mTexturedObjects.size(); i++){
		mTexturedObjects[i]->setScaleFY(-1);
		//mObjects[i]->transFY = -2;
		mTexturedObjects[i]->display();
		if (i != 0) //El suelo no incrementa el yaw
		{
			//mObjects[i]->incrementYaw(0.01);
		}
		mTexturedObjects[i]->setScaleFY(1);
	}

	glDisable(GL_STENCIL_TEST);

	glFrontFace(GL_CCW);
	//Se dibuja normal
	
	
	
	reshape(gpWindow, gWidth, gHeight);

	gpScene->setProjectionMatrix(gpScene->getProjectionMatrix() * glm::lookAt(gpCamera->getPosition(), gpCamera->getPosition() + gpCamera->getFront(), gpCamera->getUp()));

	for (int i = 0; i < mTexturedObjects.size(); i++){
		mTexturedObjects[i]->display();
	}

	

}

