#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"

struct TextureParameters
{
	const std::string image;
	const std::string texType;
	GLuint slot;
	GLenum format;
	GLenum pixelType;
};

class UTexture
{
public:
	GLuint ID;
	std::string type;
	GLuint unit;

	UTexture(const TextureParameters& textureParameters);

	void TexUnit(Shader& shader, const char* uniform, unsigned int unit); // Selects a shader uniform sampler to use a specified texture unit
	void Bind();
	void UnBind();
	void Delete();
};

