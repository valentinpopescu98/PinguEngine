#include "VBO.h"

void VBO::Create(std::vector<GLfloat> vertices)
{
	glGenBuffers(1, &id); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW); // Send vertices to VBO
}

void VBO::Create(std::vector<VertexStruct> vertices)
{
	glGenBuffers(1, &id); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexStruct), &vertices[0], GL_STATIC_DRAW); // Send vertices to VBO
}

void VBO::Delete()
{
	glDeleteBuffers(1, &id); // Delete VBO
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}