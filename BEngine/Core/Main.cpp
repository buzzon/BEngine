#include "BEngine.h"
#include "ShaderProgram.h"
#include "Model.h"

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
	face_manager::clipping_faces(face_manager::face::front, face_manager::bypass::right);

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

	
	model ourModel("nanosuit.obj");


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

		// Camera/View transformation
		auto view = engine.camera.get_view_matrix();
		auto projection = engine.camera.get_projection_matrix(static_cast<GLfloat>(b_engine::width) / static_cast<GLfloat>(b_engine::height));
		lighting_shader.set_mat4("view", view);
		lighting_shader.set_mat4("projection", projection);

		// render the loaded model
		auto model = glm::mat4();
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		lighting_shader.set_mat4("model", model);
		ourModel.draw(lighting_shader);

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
