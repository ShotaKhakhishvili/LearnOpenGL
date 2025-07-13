#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

	void TexUnit(Shader& shader, const char* uniform, GLuint unit); // Selects a shader uniform sampler to use a specified texture unit
	void Bind();
	void UnBind();
	void Delete();
};

