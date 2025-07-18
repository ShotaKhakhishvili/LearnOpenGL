#pragma once
#include "VBO.h"
#include "EBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void UnBind();
	void Delete();
};

