#include "BEngine.h"

BEngine engine;

int main()
{
	engine.CreateWindow(800, 600, "SandBox", nullptr, nullptr);
	glfwMakeContextCurrent(engine.window);
	engine.UsingGlew();

	while (!glfwWindowShouldClose(engine.window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(engine.window);
	}
	return 0;
}