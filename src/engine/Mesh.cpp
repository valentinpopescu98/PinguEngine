#include "Mesh.h"

// Overload for drawing with texture
void Mesh::CreateMesh(Shader& shader, const char* modelUni, VAO& vao, Texture& texture, GLenum drawMode, GLsizei count,
	GLuint colorUniform, GLuint textureUniform, glm::vec3 color, GLuint textureSlot, glm::vec3 position)
{
	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	UpdateMatrixUniforms(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU

	glUniform3f(colorUniform, color.r, color.g, color.b); // Add color value to the color uniform
	glUniform1i(textureUniform, textureSlot); // Set texure unit for the 2D sampler

	texture.Bind(GL_TEXTURE_2D); // Bind the texture as 2D texture
	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// Overload for drawing without texture
void Mesh::CreateMesh(Shader& shader, const char* modelUni, VAO& vao, GLenum drawMode, GLsizei count,
	GLuint colorUniform, glm::vec3 color, glm::vec3 position)
{
	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	UpdateMatrixUniforms(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU

	glUniform3f(colorUniform, color.r, color.g, color.b); // Add color value to the color uniform

	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// TODO: to implement with assimp
void Mesh::ImportMesh() {}