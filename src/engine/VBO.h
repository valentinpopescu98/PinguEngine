#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Utils.h"

class VBO : public Utils
{
	public:
		void Create(std::vector<GLfloat> vertices);
		void Create(std::vector<VertexStruct> vertices);
		void Delete();
		void Bind();
		void Unbind();

		GLuint id;
};