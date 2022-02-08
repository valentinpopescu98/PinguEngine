#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Mesh.h"
#include "Texture.h"

class Model
{
	public:
		void Import(Model& parent, std::string modelPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		void Import(Model& parent, std::string modelPath, std::string texturesDirPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		void DeleteBuffers();
		void CreateTextures(GLuint firstTextureID);
		void DeleteTextures();
		void Draw(GLuint shaderID);

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 color;

		GLuint nextTextureID;
	private:
		int CheckErrors(const aiScene* scene, Assimp::Importer& importer);
		std::vector<TextureStruct> ReadTexturesOfType(aiMaterial* mat, aiTextureType type, std::string typeName);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessNode(aiNode* node, const aiScene* scene);

		// Variables for Mesh class
		GLuint shaderID;

		// Variables for Model class
		std::vector<TextureStruct> textures;
		std::vector<Mesh> meshes;
		std::string texturesDirPath;

		Mesh origin;
};