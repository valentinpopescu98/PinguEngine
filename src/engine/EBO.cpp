#include "EBO.h"

void EBO::Create(std::vector<GLuint> indices)
{
	glGenBuffers(1, &id); // Create a EBO buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); //Bind EBO buffer to EBO target
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); // Send indices to EBO
}

void EBO::Delete()
{
	glDeleteBuffers(1, &id); // Delete EBO
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); //Bind EBO buffer to EBO target
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind EBO
}