#include "VBO.h"

void VBO::Create(float vertices[], GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Send vertices to VBO
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID); // Delete VBO
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind VBO buffer to VBO target
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}