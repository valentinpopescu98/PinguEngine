#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

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
        void CreateBuffers(std::vector<VertexStruct> vertices, std::vector<unsigned int> indices, std::vector<TextureStruct> textures);
        void DeleteBuffers();
        void Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color);

        // Mesh data
        std::vector<VertexStruct> vertices;
        std::vector<GLuint> indices;
        std::vector<TextureStruct> textures;

        glm::vec3 position;
        glm::vec3 color;

    private:
        void UseTextures(GLuint shaderID);
        void UseTextures(GLuint shaderID, glm::vec4 borderColor);

        // Render data
        VAO vao;
        VBO vbo;
        EBO ebo;
        Texture texture;
};