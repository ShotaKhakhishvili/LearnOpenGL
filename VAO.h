#pragma once
#include "VBO.h"
#include "EBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void LinkVBO(VBO VBO, GLuint layout);

	void Bind();
	void UnBind();
	void Delete();
};

