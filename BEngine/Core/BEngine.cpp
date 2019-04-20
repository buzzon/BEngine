#include "BEngine.h"

void BEngine::WriteSpecifications() {
	Message("Maximum nr of vertex attributes supported: " + std::to_string(GetMaxNR()));
}

void BEngine::CalculateDeltaTime() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void BEngine::SetEnables(GLenum cap, ...)
{
	GLenum *p = &cap;
	while (*p) {
		glEnable(cap);
		p++;
	}
}

GLfloat BEngine::GetDeltaTime() {
	return deltaTime;
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
	glfwWindowHint(GLFW_SAMPLES, 4);
	Message("Starting engine");
}

BEngine::~BEngine() {
	glfwTerminate();
	Message("Successfully disabled!");
}

void BEngine::UsingGlew() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		CauseExeption("Failed to initialize GLEW.");
}
