#include "Mesh.h"

void Mesh::InitLight(Shader& shader, glm::mat4 view, glm::mat4 projection)
{
	SendMatrix4x4_Uniform(shader.ID, "view", view); // Send view matrix as uniform to the GPU
	SendMatrix4x4_Uniform(shader.ID, "projection", projection); // Send projection matrix as uniform to the GPU
}

void Mesh::InitObject(Shader& shader, Mesh& lightSource, Camera& camera,
	glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::mat4 view, glm::mat4 projection)
{
	Send3f_Uniform(shader.ID, "material.ambient", ambient);
	Send3f_Uniform(shader.ID, "material.diffuse", diffuse);
	Send3f_Uniform(shader.ID, "material.specular", specular);
	Send1f_Uniform(shader.ID, "material.shininess", shininess);
	Send3f_Uniform(shader.ID, "lightColor", lightSource.color); // Send light color as uniform to the GPU
	Send3f_Uniform(shader.ID, "lightPos", lightSource.position); // Send light position as uniform to the GPU
	Send3f_Uniform(shader.ID, "camPos", camera.position); // Send camera position as uniform to the GPU
	SendMatrix4x4_Uniform(shader.ID, "view", view); // Send view matrix as uniform to the GPU
	SendMatrix4x4_Uniform(shader.ID, "projection", projection); // Send projection matrix as uniform to the GPU
}

// Overload for drawing default mesh with texture
void Mesh::Create(Shader& shader, VAO& vao, Texture& texture, const char* modelUni, const char* colorUni, const char* textureUni,
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

// Overload for drawing default mesh without texture
void Mesh::Create(Shader& shader, VAO& vao, const char* modelUni, const char* colorUni,
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
void Mesh::Import(const char* meshPath)
{
	
}