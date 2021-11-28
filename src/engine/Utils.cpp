#include "Utils.h"

std::string Utils::GetFileContents(const char* filePath)
{
	std::ifstream in(filePath, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	throw(errno + " ERROR: Could not open file.");
}

std::vector<std::string> Utils::GetFileLines(const char* filePath)
{
	std::ifstream in(filePath);
	std::string line;
	std::vector<std::string> lines;

	if (in)
	{
		while (std::getline(in, line))
		{
			lines.push_back(line);
		}

		return lines;
	}

	throw(errno + " ERROR: Could not open file.");
}

void Utils::SendMatrix4x4_Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Set matrix value for the uniform
}

void Utils::Send1i_Uniform(GLuint shaderID, const char* uniform, int value)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform1i(location, value); // Set value for the uniform
}

void Utils::Send3f_Uniform(GLuint shaderID, const char* uniform, glm::vec3 values)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform3f(location, values.x, values.y, values.z); // Set values for the uniform
}