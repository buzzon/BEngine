#include "BEngine.h"

BEngine engine;

// Function prototypes
bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void do_movement(); // Передвижение наблюдателя 

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
double	lastX = 400,
lastY = 300;
GLfloat sensitivity = 0.05;

bool LineMode = false; // Метод отрисовки полигонов

void loadPermInShader()
{
	GLfloat mixValue = 0.2f;

	// В цикле
	glUniform1f(glGetUniformLocation(engine.shaderProgram.program, "mixValue"), mixValue);

	// Texture control
	if (keys[GLFW_KEY_UP] && mixValue < 1.0f)
		mixValue += 1.0f * engine.GetDeltaTime();
	if (keys[GLFW_KEY_DOWN] && mixValue > 0.0f)
		mixValue -= 1.0f * engine.GetDeltaTime();
}

int main()
{
	engine.window.CreateWindow(BEngine::WIDTH, BEngine::HEIGHT, "SandBox");
	engine.SetEnables(GL_DEPTH_TEST, GL_MULTISAMPLE);
	engine.faceManager.ClippingFaces(FaceManager::Face::FRONT, FaceManager::Bypass::RIGHT);

	// Set the required callback functions
	engine.window.SetKeyCallback(key_callback);
	engine.window.SetMouseCallback(mouse_callback);

	engine.UsingGlew();
	engine.WriteSpecifications();

	engine.shaderProgram.CreateProgram();
	engine.shaderProgram.AddShader(GL_VERTEX_SHADER, "Shaders/VertexShader.vert");
	engine.shaderProgram.AddShader(GL_FRAGMENT_SHADER, "Shaders/FragmentShader.frag");

	// Load Model
	float vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left     
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Create Buffers
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Атрибут с текстой
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Атрибут с цветом
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Load and create a texture 
	GLuint texture_box = Texture::LoadTexture("container.jpg", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);
	GLuint texture_face = Texture::LoadTexture("awesomeface.png", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);

	engine.camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	engine.window.SetCursorPos(BEngine::WIDTH / 2, BEngine::HEIGHT / 2);
	while (!engine.window.WindowShouldClose())
	{
		engine.CalculateDeltaTime();

		glfwPollEvents();
		do_movement();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.shaderProgram.Use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_box);
		glUniform1i(glGetUniformLocation(engine.shaderProgram.program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_face);
		glUniform1i(glGetUniformLocation(engine.shaderProgram.program, "ourTexture2"), 1);

		// Работа с камерой (наблюдателем)

		// Camera/View transformation
		glm::mat4 view = engine.camera.GetViewMatrix();
		glm::mat4 projection = engine.camera.GetProjectionMatrix((GLfloat)BEngine::WIDTH / (GLfloat)BEngine::HEIGHT);

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(engine.shaderProgram.program, "model");
		GLint viewLoc = glGetUniformLocation(engine.shaderProgram.program, "view");
		GLint projLoc = glGetUniformLocation(engine.shaderProgram.program, "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw container
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		engine.window.SwapBuffers();
	}
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);


	if (key == GLFW_KEY_F3 && action == GLFW_PRESS) {
		if (!LineMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		LineMode = !LineMode;
	}

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		engine.camera.Move(Camera_Movement::FORWARD, engine.GetDeltaTime());
	if (keys[GLFW_KEY_S])
		engine.camera.Move(Camera_Movement::BACKWARD, engine.GetDeltaTime());
	if (keys[GLFW_KEY_A])
		engine.camera.Move(Camera_Movement::LEFT, engine.GetDeltaTime());
	if (keys[GLFW_KEY_D])
		engine.camera.Move(Camera_Movement::RIGHT, engine.GetDeltaTime());
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	engine.camera.Rotate(xoffset, yoffset);
};
