#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

class Shader
{
	public:
		void Create(const char* vertexShaderLocation, const char* fragmentShaderLocation);

		void Delete();
		void Use();

		GLuint ID;
	private:
		static std::string GetFileContents(const char* fileLocation);
		static void CompileErrors(GLuint shader, const char* type);
};