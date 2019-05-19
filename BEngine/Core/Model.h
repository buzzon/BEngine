#pragma once
#include "ShaderProgram.h"
#include <vector>
#include "Mesh.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class model
{
public:
	explicit model(const char *path)
	{
		load_model(path);
	}
	void draw(shader_program shader);
private:
	std::vector<mesh> meshes_;
	std::string directory_;
	void load_model(const std::string path);
	void process_node(aiNode *node, const aiScene *scene);
	static mesh process_mesh(aiMesh *aimesh, const aiScene *scene);
	static std::vector<b_texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string type_name);
};

