#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"

class VAO
{
	public:
		void Create();
		void Delete();
		void Bind();
		void Unbind();
		void LinkVBO(VBO& vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr);

		GLuint id;
};