#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class EBO
{
	public:
		void Create(std::vector<GLuint> indices);
		void Delete();
		void Bind();
		void Unbind();

		GLuint id;
};