#include "BEngine.h"

BEngine engine;
GLfloat mixValue = 0.2f;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{	engine.CreateWindow(800, 600, "SandBox", nullptr, nullptr);
	glfwMakeContextCurrent(engine.window);

	// Set the required callback functions
	glfwSetKeyCallback(engine.window, key_callback);

	engine.UsingGlew();

	engine.WriteSpecifications();

	engine.shaderProgram.CreateProgram();
	engine.shaderProgram.AddShader(GL_VERTEX_SHADER, "Shaders/VertexShader.vert");
	engine.shaderProgram.AddShader(GL_FRAGMENT_SHADER, "Shaders/FragmentShader.frag");

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3 
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Атрибут с цветом
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Атрибут с текстой
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Load and create a texture 
	GLuint texture1 = Texture::LoadTexture("container.jpg", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);
	GLuint texture2 = Texture::LoadTexture("awesomeface.png", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);

	while (!glfwWindowShouldClose(engine.window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		engine.shaderProgram.Use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(engine.shaderProgram.program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(engine.shaderProgram.program, "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(engine.shaderProgram.program, "mixValue"), mixValue);

		//Трансформация
		glm::mat4 transform;
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(engine.shaderProgram.program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(engine.window);
	}
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		if (mixValue < 1.0f)
			mixValue += 0.01f;
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		if (mixValue > 0.0f)
			mixValue -= 0.01f;
}