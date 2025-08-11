#include "Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = texType;

	int width, height, numColCh;																// Self-explanatory
	stbi_set_flip_vertically_on_load(true);														// Fixing the allignment error between stbi and openGL
	unsigned char* bytes = stbi_load(image, &width, &height, &numColCh, 0);						// Reading the texture image

	glGenTextures(1, &ID);																		// Creating a texture on the GPU
	glActiveTexture(GL_TEXTURE0 + slot);														// Activating the specified texture unit
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);															// Binding the given texture
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);							// Scaling type when scaled down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);							// Scaling type when scaled up

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);								// Wrapping mode on axis S (horizontal)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);								// Wrapping mode on axis T (vertical)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);		// Specify the 2D texture image and upload pixel data to the GPU
	glGenerateMipmap(GL_TEXTURE_2D);															// Generating mipmaps

	stbi_image_free(bytes);																		// Deallocating the image data, since its no longer used
	glBindTexture(GL_TEXTURE_2D, 0);															// Unbinding to avoid accidental changes
}


// Selects a shader uniform sampler to use a specified texture unit
void Texture::TexUnit(Shader& shader, const char* uniform, unsigned int unit)
{
	GLuint texUniform = glGetUniformLocation(shader.ID, uniform);		// Gets the location of the sampler	
	shader.Activate();													// Activates the shader program
	glUniform1i(texUniform, unit);										// Sets the sampler uniform to use the specified texture unit
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
