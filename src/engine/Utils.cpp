#include "Utils.h"

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