#include "BEngine.h"
#include "ShaderProgram.h"
#include <SOIL/SOIL.h>
#include "Texture.h"

b_engine engine;

bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void camera_control();

double last_x = static_cast<float>(b_engine::width) / 2;
double last_y = static_cast<float>(b_engine::height) / 2;

glm::vec3 light_pos(-0.2f, -1.0f, -0.3f);

bool line_mode = false; // Метод отрисовки полигонов dady is best

int main()
{
	engine.window.create_window(b_engine::width, b_engine::height, "SandBox");
	b_engine::set_enables(GL_DEPTH_TEST, GL_MULTISAMPLE);
	//face_manager::clipping_faces(face_manager::face::front, face_manager::bypass::right);

	// Set the required callback functions
	engine.window.set_key_callback(key_callback);
	engine.window.set_mouse_callback(mouse_callback);

	b_engine::using_glew();
	engine.write_specifications();


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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	glm::vec3 cube_positions[] = {
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	// Атрибут с нормалью
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Атрибут с текстурой
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// lightVAO
	GLuint light_vao;
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load and create a texture 
	const auto texture_box = texture::load_texture("container2.png", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);
	const auto texture_box_specular = texture::load_texture("container2_specular.png", GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);

	// shader configuration
// --------------------
	lighting_shader.use();
	lighting_shader.set_int("material.diffuse", 0);
	lighting_shader.set_int("material.specular", 1);

	engine.camera = camera(glm::vec3(0.0f, 0.0f, 3.0f));

	engine.window.set_cursor_pos(b_engine::width / 2, b_engine::height / 2);
	while (!engine.window.window_should_close())
	{
		engine.calculate_delta_time();

		glfwPollEvents();
		camera_control();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		lighting_shader.use();
		light_pos.z = engine.camera.get_position().z;
		lighting_shader.set_vec3("light.direction", light_pos);
		lighting_shader.set_vec3("viewPos", engine.camera.get_position());

		// light properties
		lighting_shader.set_vec3("light.ambient", glm::vec3(0.1f));
		lighting_shader.set_vec3("light.diffuse", glm::vec3(1.0f));
		lighting_shader.set_vec3("light.specular", glm::vec3(1.0f));

		// material properties
		lighting_shader.set_vec3("material.specular", glm::vec3(0.5f));
		lighting_shader.set_float("material.shininess", 64.0f);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_box);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_box_specular);

		// Camera/View transformation
		auto view = engine.camera.get_view_matrix();
		auto projection = engine.camera.get_projection_matrix(static_cast<GLfloat>(b_engine::width) / static_cast<GLfloat>(b_engine::height));

		// Get their uniform location
		auto model_loc = glGetUniformLocation(lighting_shader.program, "model");
		auto view_loc = glGetUniformLocation(lighting_shader.program, "view");
		auto proj_loc = glGetUniformLocation(lighting_shader.program, "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(container_vao);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cube_positions[i]);
			auto angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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
		auto model = glm::mat4();
		model = glm::translate(model, light_pos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(light_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		engine.window.swap_buffers();
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

void camera_control()
{
	if (keys[GLFW_KEY_W])
		engine.camera.move(camera::movement::forward, engine.get_delta_time());
	if (keys[GLFW_KEY_S])
		engine.camera.move(camera::movement::backward, engine.get_delta_time());
	if (keys[GLFW_KEY_A])
		engine.camera.move(camera::movement::left, engine.get_delta_time());
	if (keys[GLFW_KEY_D])
		engine.camera.move(camera::movement::right, engine.get_delta_time());
}

void mouse_callback(GLFWwindow* window, const double x_pos, const double y_pos)
{
	const GLfloat x_offset = x_pos - last_x;
	const GLfloat y_offset = last_y - y_pos;

	if (last_x != x_pos || last_y != y_pos)
	{
		engine.camera.rotate(x_offset, y_offset);

		last_x = x_pos;
		last_y = y_pos;
	}
};
