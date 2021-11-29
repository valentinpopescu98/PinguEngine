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
    GLuint id;
    std::string type;
    const char* path;
};

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