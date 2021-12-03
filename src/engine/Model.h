#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Mesh.h"
#include "Texture.h"

class Model : public Utils
{
	public:
		void Import(std::string meshPath);
		void Import(std::string meshPath, std::vector<TextureStruct> customTextures);
		void Import(std::string meshPath, std::string texturesDirPath);
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 color);
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 color, GLenum textureDimension, GLint interpType, GLint wrapType);
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 color, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
		void DeleteTextures();
	private:
		int CheckErrors(const aiScene* scene, Assimp::Importer& importer);
		GLuint TextureFromFile(const char* path);
		std::vector<TextureStruct> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessNode(aiNode* node, const aiScene* scene);

		// Variables for Mesh class
		GLuint shaderID;
		std::vector<TextureStruct> customTextures;

		// Variables for Model class
		std::vector<TextureStruct> texturesLoaded;
		std::vector<Mesh> meshes;
		std::string texturesDirPath;
		int hasTexture;
};