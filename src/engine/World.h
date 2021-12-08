#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "XMLParser.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Culler.h"

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
		XMLParser parser;
		Shader objectShader, lightShader;
		Camera camera;
		std::vector<Mesh> meshLights, meshObjects;

		// UNIFORMS
		glm::mat4 view, projection;
};