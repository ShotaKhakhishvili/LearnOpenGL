#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);												//	Creating a buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, ID);									//	Binding the buffer as a type of GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);		//	Attaching the data to the buffer
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}