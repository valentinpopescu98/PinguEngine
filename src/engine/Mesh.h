#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
#include <iostream>

#include "Utils.h"
#include "Engine.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh : public Utils
{
	public:
		void InitLight(Shader& shader, glm::mat4 view, glm::mat4 projection);
		void InitObject(Shader& shader, Mesh& lightSource, Camera& camera,
			glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::mat4 view, glm::mat4 projection);
		void Create(Shader& shader, VAO& vao, Texture& texture, const char* modelUni, const char* colorUni, const char* textureUni,
			glm::vec3 color, glm::vec3 position, GLuint textureSlot, GLenum drawMode, GLsizei count);
		void Create(Shader& shader, VAO& vao, const char* modelUni, const char* colorUni,
			glm::vec3 color, glm::vec3 position, GLenum drawMode, GLsizei count);
		void Import(const char* meshPath);

		glm::vec3 position;
		glm::vec3 color;

	private:
		// ONLY FOR IMPORTED MESHES
		/*std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		VAO vao;
		VBO vbo;
		EBO ebo;*/
};