#include "Mesh.h"

// Overload for drawing with texture
void Mesh::CreateMesh(Shader& shader, VAO& vao, Texture& texture, const char* modelUni, const char* colorUni, const char* textureUni,
	glm::vec3 color, glm::vec3 position, GLuint textureSlot, GLenum drawMode, GLsizei count)
{
	this->color = color;
	this->position = position;

	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	SendMatrix4x4_Uniform(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU
	Send3f_Uniform(shader.ID, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU
	Send1i_Uniform(shader.ID, textureUni, textureSlot); // Send texture slot as uniform to the GPU

	texture.Bind(GL_TEXTURE_2D); // Bind the texture as 2D texture
	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// Overload for drawing without texture
void Mesh::CreateMesh(Shader& shader, VAO& vao, const char* modelUni, const char* colorUni,
	glm::vec3 color, glm::vec3 position, GLenum drawMode, GLsizei count)
{
	this->color = color;
	this->position = position;

	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	SendMatrix4x4_Uniform(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU
	Send3f_Uniform(shader.ID, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU

	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// TODO: to implement with assimp
void Mesh::ImportMesh()
{

}