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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() const
{
	glUseProgram(ID);
}

void Shader::Delete() const
{
	glDeleteProgram(ID);
}
