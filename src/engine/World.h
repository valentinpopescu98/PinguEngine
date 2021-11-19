#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Utils.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class World : public Utils
{
	public:
		void Init();
		void End();
		void Run(GLFWwindow* window);

		double previousTime = 0;
		double elapsedTime = 0;
		double deltaTime = 0;
	private:
		void BeforeDrawing();
		void Draw(GLFWwindow* window);
		void AfterDrawing(GLFWwindow* window);
		void SetTimeValues();

		// INSTANCES
		Camera camera;
		Shader objectShader, lightShader;
		Mesh objectMesh, lightMesh;
		Texture texture;
		VAO objectVAO, lightVAO;
		VBO objectVBO, lightVBO;
		EBO objectEBO, lightEBO;

		// UNIFORMS
		GLuint color0Loc, text0Loc;
		glm::mat4 view, projection;
};