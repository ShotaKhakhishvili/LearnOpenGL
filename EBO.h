#pragma once

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint>& indices);

	void Bind()const;
	void UnBind()const;
	void Delete()const;
};

