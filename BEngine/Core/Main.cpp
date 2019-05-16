#include "BEngine.h"

BEngine engine;

bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void do_movement(); 

double last_x = static_cast<float>(BEngine::WIDTH) / 2;
double last_y = static_cast<float>(BEngine::HEIGHT) / 2;

glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

bool line_mode = false; // Метод отрисовки полигонов

int main()
{
	engine.window.CreateWindow(BEngine::WIDTH, BEngine::HEIGHT, "SandBox");
	engine.SetEnables(GL_DEPTH_TEST, GL_MULTISAMPLE);
	//engine.faceManager.ClippingFaces(FaceManager::Face::FRONT, FaceManager::Bypass::RIGHT);

	// Set the required callback functions
	engine.window.SetKeyCallback(key_callback);
	engine.window.SetMouseCallback(mouse_callback);

	engine.UsingGlew();
	engine.WriteSpecifications();


	shader_program lighting_shader;
	lighting_shader.create_program();
	lighting_shader.add_shader(GL_VERTEX_SHADER, "Shaders/Lighting.vert");
	lighting_shader.add_shader(GL_FRAGMENT_SHADER, "Shaders/Lighting.frag");

	shader_program lamp_shader;
	lamp_shader.create_program();
	lamp_shader.add_shader(GL_VERTEX_SHADER, "Shaders/Lamp.vert");
	lamp_shader.add_shader(GL_FRAGMENT_SHADER, "Shaders/Lamp.frag");
	const auto light_color = glm::vec3(1.0f, 1.0f, 1.0f);

	// Load Model
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

	// Create Buffers
	GLuint vbo, container_vao;
	glGenVertexArrays(1, &container_vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(container_vao);

	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	// Атрибут с нормалью
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	// lightVAO
	GLuint light_vao;
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load and create a texture 
	//GLuint texture_box = Texture::LoadTexture("container.jpg", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);
	//GLuint texture_face = Texture::LoadTexture("awesome-face.png", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);

	engine.camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	engine.window.SetCursorPos(BEngine::WIDTH / 2, BEngine::HEIGHT / 2);
	while (!engine.window.WindowShouldClose())
	{
		engine.CalculateDeltaTime();

		glfwPollEvents();
		do_movement();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use corresponding shader when setting uniforms/drawing objects
		lighting_shader.use();
		lighting_shader.set_vec3("material.ambient", 1.0f, 0.5f, 0.31f);
		lighting_shader.set_vec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		lighting_shader.set_vec3("material.specular", 0.5f, 0.5f, 0.5f);
		lighting_shader.set_float("material.shininess", 32.0f);

		auto diffuse_color = light_color * glm::vec3(0.5f);
		auto ambient_color = diffuse_color * glm::vec3(0.2f);

		lighting_shader.set_vec3("light.ambient", ambient_color);
		lighting_shader.set_vec3("light.diffuse", diffuse_color);
		lighting_shader.set_vec3("light.specular", 1.0f, 1.0f, 1.0f);

		lighting_shader.set_vec3("lightPos", light_pos.x, light_pos.y, light_pos.z);
		const auto player_pos = engine.camera.GetPosition();
		lighting_shader.set_vec3("viewPos", player_pos.x, player_pos.y, player_pos.z);

		// Bind Textures using texture units
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture_box);
		//glUniform1i(glGetUniformLocation(lightingShader.program, "ourTexture1"), 0);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture_face);
		//glUniform1i(glGetUniformLocation(lightingShader.program, "ourTexture2"), 1);

		// Camera/View transformation
		glm::mat4 view = engine.camera.GetViewMatrix();
		glm::mat4 projection = engine.camera.GetProjectionMatrix(static_cast<GLfloat>(BEngine::WIDTH) / static_cast<GLfloat>(BEngine::HEIGHT));

		// Get their uniform location
		auto model_loc = glGetUniformLocation(lighting_shader.program, "model");
		auto view_loc  = glGetUniformLocation(lighting_shader.program, "view");
		auto proj_loc  = glGetUniformLocation(lighting_shader.program, "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(container_vao);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			auto angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lamp_shader.use();
		lamp_shader.set_vec3("color", light_color);

		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		model_loc = glGetUniformLocation(lamp_shader.program, "model");
		view_loc = glGetUniformLocation(lamp_shader.program, "view");
		proj_loc = glGetUniformLocation(lamp_shader.program, "projection");
		// Set matrices
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 model = glm::mat4();
		model = glm::translate(model, light_pos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(light_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		engine.window.SwapBuffers();
	}
	return 0;
}

void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F3 && action == GLFW_PRESS) {
		if (!line_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		line_mode = !line_mode;
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
		engine.camera.Move(Camera::Movement::FORWARD, engine.GetDeltaTime());
	if (keys[GLFW_KEY_S])
		engine.camera.Move(Camera::Movement::BACKWARD, engine.GetDeltaTime());
	if (keys[GLFW_KEY_A])
		engine.camera.Move(Camera::Movement::LEFT, engine.GetDeltaTime());
	if (keys[GLFW_KEY_D])
		engine.camera.Move(Camera::Movement::RIGHT, engine.GetDeltaTime());
}

void mouse_callback(GLFWwindow* window, const double x_pos, const double y_pos)
{
	const GLfloat x_offset = x_pos - last_x;
	const GLfloat y_offset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	engine.camera.Rotate(x_offset, y_offset);
};
