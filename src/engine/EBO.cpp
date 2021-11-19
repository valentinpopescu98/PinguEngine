#include "EBO.h"

void EBO::Create(unsigned int indices[], GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Create a EBO buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //Bind EBO buffer to EBO target
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); // Send indices to EBO
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID); // Delete EBO
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //Bind EBO buffer to EBO target
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind EBO
}