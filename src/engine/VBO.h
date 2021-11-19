#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO
{
	public:
		void Create(float vertices[], GLsizeiptr size);
		void Delete();
		void Bind();
		void Unbind();

		GLuint ID;
};