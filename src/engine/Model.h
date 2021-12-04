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
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, GLenum textureDimension, GLint interpType, GLint wrapType);
		void Render(GLuint shaderID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
		void RenderChild(GLuint shaderID, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		void RenderChild(GLuint shaderID, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, GLenum textureDimension, GLint interpType, GLint wrapType);
		void RenderChild(GLuint shaderID, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
		void DeleteTextures();

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 color;
	private:
		void CreateTextures(GLuint shaderID, Mesh& mesh, GLenum textureDimension, GLint interpType, GLint wrapType);
		void CreateTextures(GLuint shaderID, Mesh& mesh, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
		int CheckErrors(const aiScene* scene, Assimp::Importer& importer);
		void TextureFromFile(const char* path);
		std::vector<TextureStruct> ReadTexturesOfType(aiMaterial* mat, aiTextureType type, std::string typeName);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessNode(aiNode* node, const aiScene* scene);

		// Variables for Mesh class
		GLuint shaderID;

		// Variables for Model class
		std::vector<TextureStruct> textures;
		std::vector<Mesh> meshes;
		std::string texturesDirPath;
		int hasTexture;
};