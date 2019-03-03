#include "BEngine.h"

BEngine::BEngine()
{
	Message("Initializing GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWVERMAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWVERMINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Message("Starting engine");
}

BEngine::~BEngine()
{
	glfwTerminate();
}

void BEngine::Message(const char *message)
{
	printf("[%s] : %s \n", BName, message);
}

void BEngine::ErrorMessage(const char * message)
{
	printf("[%s] [ERROR] : %s \n", BName, message);
}
