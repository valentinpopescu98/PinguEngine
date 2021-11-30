#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh : public Utils
{
	public:
        Mesh CreateBuffers(std::vector<VertexStruct> vertices, std::vector<unsigned int> indices, std::vector<TextureStruct> textures);
        void DeleteBuffers();

        void Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color);
        void Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color,
            GLenum textureDimension, GLint interpType, GLint wrapType);
        void Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color,
            GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
        void DeleteTextures();

        // Mesh data
        std::vector<VertexStruct> vertices;
        std::vector<GLuint> indices;
        std::vector<TextureStruct> textures;

        glm::vec3 position;
        glm::vec3 color;
    private:
        void CreateTextures(GLuint shaderID, GLenum textureDimension, GLint interpType, GLint wrapType);
        void CreateTextures(GLuint shaderID, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);

        // Render data
        VAO vao;
        VBO vbo;
        EBO ebo;
        Texture texture;
};