#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexPath, const char* fragmentPath);

	void Activate() const;
	void Delete() const;

	void compileErrors(unsigned int shader, const char* type);
};