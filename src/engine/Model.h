#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

#include "Mesh.h"

class Model : public Utils
{
	public:
		void Import(std::string path);
		void Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color);
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureStruct> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		std::vector<TextureStruct> texturesLoaded;
		std::vector<Mesh> meshes;
		std::string directory;
};