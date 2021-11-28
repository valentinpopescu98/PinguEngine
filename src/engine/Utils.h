#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <cerrno>

class Utils
{
public:
	std::string GetFileContents(const char* filePath);
	std::vector<std::string> GetFileLines(const char* filePath);
	void SendMatrix4x4_Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix);
	void Send1f_Uniform(GLuint shaderID, const char* uniform, float value);
	void Send1i_Uniform(GLuint shaderID, const char* uniform, int value);
	void Send3f_Uniform(GLuint shaderID, const char* uniform, glm::vec3 values);
};