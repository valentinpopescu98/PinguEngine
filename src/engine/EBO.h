#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO
{
public:
	void Create(unsigned int indices[], GLsizeiptr size);

	void Delete();
	void Bind();
	void Unbind();

	GLuint ID;
};