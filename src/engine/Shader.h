#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Utils.h"

class Shader : public Utils
{
	public:
		void Create(const char* vertexShaderPath, const char* fragmentShaderPath);
		void Delete();
		void Use();
		void InitMatrices(glm::mat4 view, glm::mat4 projection);
		void InitMaterial(glm::vec3 lightSrcPosition, glm::vec3 lightSrcColor, glm::vec3 cameraPosition,
			glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

		GLuint id;
		glm::mat4 view, projection;
	private:
		void CheckErrors(GLuint shader, const char* type);

		std::string vertexShaderPath, fragmentShaderPath;
};