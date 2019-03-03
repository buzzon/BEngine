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
	Message("Successfully disabled!");
}

void BEngine::Message(const char *message)
{
	printf("[%s] : %s \n", BName, message);
}

void BEngine::ErrorMessage(const char * message)
{
	printf("[%s] [ERROR] : %s \n", BName, message);
}

void BEngine::CauseExeption(const char * message)
{
	ErrorMessage(message);
	system("pause");
	throw std::invalid_argument(message);
}

void BEngine::CreateWindow(int width, int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share)
{
	window = glfwCreateWindow(width, height, title, monitor, share);
	if (window == nullptr)
	{
		glfwTerminate();
		CauseExeption("Failed to create GLFW window.");
	}
	else
		glViewport(0, 0, width, height);
}

void BEngine::UsingGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		CauseExeption("Failed to initialize GLEW.");
}
