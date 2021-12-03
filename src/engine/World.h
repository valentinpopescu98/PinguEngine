#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"

class World : public Utils
{
	public:
		void Init();
		void End();
		void Run(GLFWwindow* window);
	private:
		void BeforeDrawing();
		void Draw(GLFWwindow* window);
		void AfterDrawing(GLFWwindow* window);

		// INSTANCES
		Camera camera;
		Shader objectShader, lightShader;
		Mesh meshLightSource, meshObject;
		Model modelObject, modelObject2;

		// UNIFORMS
		glm::mat4 view, projection;
};