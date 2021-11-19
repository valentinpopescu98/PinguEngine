#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Utils
{
public:
	void UpdateMatrixUniforms(GLuint shaderID, const char* uniform, glm::mat4 matrix);
};