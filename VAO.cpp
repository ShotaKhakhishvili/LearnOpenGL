#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);		// Creating a Vertex Array on the GPU
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();																			// Binding a Vertex Buffer Object
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);		// Defining the vertex attributes for the given layout
	glEnableVertexAttribArray(layout);													// Enabling the vertex attribute array at the given location
	VBO.UnBind();																		// Unbind the VBO
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
