#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <cerrno>

struct VertexStruct
{
    glm::vec3 coords;
    glm::vec3 normals;
    glm::vec2 textCoords;
    glm::vec3 colors;
};

struct TextureStruct
{
    std::string type;
    std::string path;
};

class Utils
{
	public:
		static std::string GetFileContents(const char* filePath);
		static std::vector<std::string> GetFileLines(const char* filePath);
		static void SendMatrix4x4_Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix);
		static void Send1f_Uniform(GLuint shaderID, const char* uniform, float value);
		static void Send1i_Uniform(GLuint shaderID, const char* uniform, int value);
		static void Send3f_Uniform(GLuint shaderID, const char* uniform, glm::vec3 values);
};