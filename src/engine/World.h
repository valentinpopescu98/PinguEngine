#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "GuiDrawer.h"
#include "XMLParser.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Culler.h"
#include "CollisionManager.h"
#include "ParticleSystem.h"
#include "ScriptingSystem.h"

class World
{
	public:
		void Init(GLFWwindow* window);
		void End();
		void Run(GLFWwindow* window);

		std::vector<Model> modelLights, modelObjects;
	private:
		void BeforeUpdate(GLFWwindow* window);
		void Update(GLFWwindow* window);
		void AfterUpdate(GLFWwindow* window);
		void ReloadModels();

		// INSTANCES
		XmlParser parser;
		ParticleSystem particleSystem;
		Shader objectShader, lightShader;
		Camera camera;
		std::vector<Mesh> meshLights, meshObjects;
		Mesh origin;

		// UNIFORMS
		glm::mat4 view, projection;
};