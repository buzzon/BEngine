#include "BEngine.h"

void BEngine::WriteSpecifications() {
	Message("Maximum nr of vertex attributes supported: " + std::to_string( GetMaxNR() ) );
}

int BEngine::GetMaxNR() {
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	return nrAttributes; 
}

BEngine::BEngine() {
	Message("Initializing GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWVERMAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWVERMINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Message("Starting engine");
}

BEngine::~BEngine() {
	glfwTerminate();
	Message("Successfully disabled!");
}

void BEngine::CreateWindow(	int width,
							int height,
							const char * title,
							GLFWmonitor * monitor,
							GLFWwindow * share) {
	window = glfwCreateWindow(width, height, title, monitor, share);
	if (window == nullptr) {
		glfwTerminate();
		CauseExeption("Failed to create GLFW window.");
	} else {
		glViewport(0, 0, width, height);
		glfwMakeContextCurrent(window);
	}
}

void BEngine::UsingGlew() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		CauseExeption("Failed to initialize GLEW.");
}
