#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "ShaderProgram.h"

struct vertex {
	// position
	glm::vec3 position;
	// normal
	glm::vec3 normal;
	// texCoords
	glm::vec2 tex_coords;
	// tangent
	glm::vec3 tangent;
	// bitangent
	glm::vec3 bitangent;
};

struct b_texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class mesh
{
public:
	/*  Mesh Data  */
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<b_texture> textures;
	unsigned int VAO;
	mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<b_texture> textures);
	void draw(shader_program shader);
private:
	/*  Render data  */
	unsigned int VBO, EBO;
	void setup_mesh();
};

