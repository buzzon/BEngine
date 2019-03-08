#include "BEngine.h"

BEngine engine;

int main()
{	engine.CreateWindow(800, 600, "SandBox", nullptr, nullptr);
	glfwMakeContextCurrent(engine.window);
	engine.UsingGlew();

	engine.WriteSpecifications();

	engine.shaderProgram.CreateProgram();
	engine.shaderProgram.AddShader(GL_VERTEX_SHADER, "Shaders/VertexShader.glsl");
	engine.shaderProgram.AddShader(GL_FRAGMENT_SHADER, "Shaders/FragmentShader.glsl");


	GLfloat vertices[] = {
		// Позиции         // Цвета
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Нижний правый угол
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Нижний левый угол
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Верхний угол
	};
	GLuint indices[] = {  // Помните, что мы начинаем с 0!
		0, 1, 2,   // Первый треугольник
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Атрибут с цветом
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(engine.window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		engine.shaderProgram.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(engine.window);
	}
	return 0;
}