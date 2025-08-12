#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

struct ShaderParameters
{
	const std::string vertShader;
	const std::string fragShader;
};

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	void Activate() const;
	void Delete() const;

	void compileErrors(unsigned int shader, const char* type);
};