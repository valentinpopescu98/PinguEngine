#include "VAO.h"

void VAO::Create()
{
	glGenVertexArrays(1, &id); // Create a VAO buffer
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

void VAO::Delete()
{
	glDeleteBuffers(1, &id); // Delete VBO
}

void VAO::Bind()
{
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

void VAO::Unbind()
{
	glBindVertexArray(0); // Unbind VAO
}

void VAO::LinkVBO(VBO& vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr)
{
	vbo.Bind();
	glVertexAttribPointer(layoutLocation, 3, GL_FLOAT, GL_FALSE, stride, startPtr); // Send VBOs to chosen layout location
	glEnableVertexAttribArray(layoutLocation); // Enable layout location
	vbo.Unbind();
}