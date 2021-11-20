#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Utils
{
public:
	void SendMatrix4x4_Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix);
	void Send1i_Uniform(GLuint shaderID, const char* uniform, int value);
	void Send3f_Uniform(GLuint shaderID, const char* uniform, glm::vec3 values);
};