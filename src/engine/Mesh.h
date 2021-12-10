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

class Mesh
{
	public:
        void CreateBuffers(std::vector<VertexStruct> vertices, std::vector<GLuint> indices,
            Mesh& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
        void CreateBuffers(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures,
            Mesh& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
        void DeleteBuffers();
        void CreateTextures(GLuint shaderID, GLuint firstTextureID, GLenum textureDimension, GLint interpType, GLint wrapType);
        void CreateTextures(GLuint shaderID, GLuint firstTextureID, GLenum textureDimension, GLint interpType, glm::vec3 borderColor);
        void DeleteTextures();
        void Draw(GLuint shaderID);

        // Mesh data
        std::vector<VertexStruct> vertices;
        std::vector<GLuint> indices;
        std::vector<TextureStruct> textures;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 color;        
    private:
        // Render data
        VAO vao;
        VBO vbo;
        EBO ebo;
        Texture texture;

        /* Variable that toggles when any of the CreateTexture overloads is called.
           To work properly, you need to create a new Mesh or Model class for every new object, even if it is of the same type. */
        bool hasTexture = false;
        GLenum textureDimension;
        GLuint firstTextureID;
};