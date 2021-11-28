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

		GLuint ID;
	private:
		void CheckErrors(GLuint shader, const char* type);
};