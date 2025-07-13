#include "shader.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (in)
	{
		std::ostringstream contents;
		contents << in.rdbuf();
		return contents.str();
	}
	else
	{
		std::cerr << "Error opening file: " << filename << std::endl;
	}
	return std::string();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertShader = get_file_contents(vertexPath);
	std::string fragShader = get_file_contents(fragmentPath);

	// Vertex Shader source code
	const char* vertexShaderSource = vertShader.c_str();
	//Fragment Shader source code
	const char* fragmentShaderSource = fragShader.c_str();

	// Creating a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);				//	Creating a vertex shader on the GPU
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);		//	Set the source code for the shader
	glCompileShader(vertexShader);										//	Compiling the source
	compileErrors(vertexShader, "VERTEX");								//	Checking for errors

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);			//	Creating a fragment shader on the GPU
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);	//	Set the source code for the shader
	glCompileShader(fragmentShader);									//  Compiling the source
	compileErrors(fragmentShader, "FRAGMENT");							//	Checking for errors
		
	ID = glCreateProgram();												//  Allocating a shader program
	glAttachShader(ID, vertexShader);									//  Attaching a vertex shader to the program
	glAttachShader(ID, fragmentShader);									//	Attaching a fragment shader to the program
	glLinkProgram(ID);													//  Linking the attached shaders into a complete program
	compileErrors(ID, "PROGRAM");										//  Checking for an error when linking


	// Deleting the shaders, since they are no longer used.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() const
{
	glUseProgram(ID);	// Set the program as the current one
}

void Shader::Delete() const
{
	glDeleteProgram(ID);	// Deallocate the program
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}
