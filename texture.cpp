#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = texType;

	int width, height, numColCh;														// Self-explanatory
	stbi_set_flip_vertically_on_load(true);												// Fixing the allignment error between stbi and openGL
	unsigned char* bytes = stbi_load(image, &width, &height, &numColCh, 0);				// Reading the texture image

	glGenTextures(1, &ID);																// Creating a texture on the GPU
	glActiveTexture(slot);																// Activating the specified texture unit
	glBindTexture(type, ID);															// Binding the given texture
		
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);							// Scaling type when scaled down
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);							// Scaling type when scaled up

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);								// Wrapping mode on axis S (horizontal)
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);								// Wrapping mode on axis T (vertical)

	glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);			// Specify the 2D texture image and upload pixel data to the GPU
	glGenerateMipmap(type);																// Generating mipmaps

	stbi_image_free(bytes);																// Deallocating the image data, since its no longer used
	glBindTexture(type, 0);																// Unbinding to avoid accidental changes
}


// Selects a shader uniform sampler to use a specified texture unit
void Texture::TexUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint texUniform = glGetUniformLocation(shader.ID, uniform);		// Gets the location of the sampler	
	shader.Activate();													// Activates the shader program
	glUniform1i(texUniform, unit);										// Sets the sampler uniform to use the specified texture unit
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::UnBind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
