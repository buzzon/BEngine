#include "BEngine.h"

#include <stdexcept>

BEngine engine;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void UsingGlew() 
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		engine.ErrorMessage("Failed to initialize GLEW.");
		system("pause");
		throw std::invalid_argument("Failed to initialize GLEW.");
	}
}

int main()
{
	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "sandbox", nullptr, nullptr);
	if (window == nullptr)
	{
		engine.ErrorMessage("Failed to create GLFW window.");
		glfwTerminate();
		system("pause");
		throw std::invalid_argument("Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	UsingGlew();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	// Start using engine
	engine.Message("Successfully launched!");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
	engine.Message("Successfully disabled!");

	return 0;
}