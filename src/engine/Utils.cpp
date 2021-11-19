#include "Utils.h"

void Utils::UpdateMatrixUniforms(GLuint shaderID, const char* uniform, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Set matrix value for the uniform
}