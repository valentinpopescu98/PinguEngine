#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "Engine.h"
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh : public Utils
{
	public:
		void CreateMesh(Shader& shader, const char* modelUni, VAO& vao, Texture& texture, GLenum drawMode, GLsizei count,
			GLuint colorUniform, GLuint textureUniform, glm::vec3 color, GLuint textureSlot, glm::vec3 position);
		void CreateMesh(Shader& shader, const char* modelUni, VAO& vao, GLenum drawMode, GLsizei count,
			GLuint colorUniform, glm::vec3 color, glm::vec3 position);
		void ImportMesh();
};