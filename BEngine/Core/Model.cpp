#include "Model.h"

void model::draw(const shader_program shader)
{
	for (auto& mesh : meshes_)
		mesh.draw(shader);
}

void model::load_model(const std::string path)
{
	Assimp::Importer import;
	const auto scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	directory_ = path.substr(0, path.find_last_of('/'));

	process_node(scene->mRootNode, scene);
}

void  model::process_node(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		const auto mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(process_mesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(node->mChildren[i], scene);
	}
}
mesh model::process_mesh(aiMesh *aimesh, const aiScene *scene) 
{
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<b_texture> textures;

	for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
	{
		vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = aimesh->mVertices[i].x;
		vector.y = aimesh->mVertices[i].y;
		vector.z = aimesh->mVertices[i].z;
		vertex.position = vector;
		// normals
		vector.x = aimesh->mNormals[i].x;
		vector.y = aimesh->mNormals[i].y;
		vector.z = aimesh->mNormals[i].z;
		vertex.normal = vector;
		// texture coordinates
		if (aimesh->mTextureCoords[0]) // does the aimesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = aimesh->mTextureCoords[0][i].x;
			vec.y = aimesh->mTextureCoords[0][i].y;
			vertex.tex_coords = vec;
		}
		else
			vertex.tex_coords = glm::vec2(0.0f, 0.0f);
		//// tangent
		//vector.x = aimesh->mTangents[i].x;
		//vector.y = aimesh->mTangents[i].y;
		//vector.z = aimesh->mTangents[i].z;
		//vertex.tangent = vector;
		//// bitangent
		//vector.x = aimesh->mBitangents[i].x;
		//vector.y = aimesh->mBitangents[i].y;
		//vector.z = aimesh->mBitangents[i].z;
		//vertex.bitangent = vector;
		vertices.push_back(vertex);
	}
	// now wak through each of the aimesh's faces (a face is a aimesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
	{
		auto face = aimesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	auto material = scene->mMaterials[aimesh->mMaterialIndex];

	// 1. diffuse maps
	auto diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
	// 2. specular maps
	auto specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	// 3. normal maps
	auto normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
	// 4. height maps
	auto height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), height_maps.begin(), height_maps.end());

	return  mesh(vertices, indices, textures);
}

std::vector<b_texture> model::load_material_textures(aiMaterial *mat, const aiTextureType type, const std::string type_name)
{
	std::vector<b_texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		b_texture texture;
		texture.id = texture::load_texture(str.C_Str(), GL_TEXTURE_2D, SOIL_LOAD_RGB, GL_RGB);
		texture.type = type_name;
		texture.path = str;
		textures.push_back(texture);
	}

	return textures;
}

