#include "BEngine.h"

BEngine::BEngine()
{
	// Initializing GLFW and installing the minimum version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWVERMAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWVERMINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


BEngine::~BEngine()
{
	glfwTerminate();
}
