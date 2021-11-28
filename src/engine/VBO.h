#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class VBO
{
	public:
		void Create(std::vector<GLfloat> vertices);
		void Delete();
		void Bind();
		void Unbind();

		GLuint ID;
};