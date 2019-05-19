#include "Model.h"

void model::draw(const shader_program shader)
{
	for (auto& mesh : meshes_)
		mesh.draw(shader);
}

void model::load_model(std::string path)
{
}

void  model::process_node(aiNode *node, const aiScene *scene)
{
	
};
mesh  model::process_mesh(aiMesh *mesh, const aiScene *scene) 
{

};

std::vector<texture>  model::load_material_textures(aiMaterial *mat, aiTextureType type, std::string type_name) 
{

};
