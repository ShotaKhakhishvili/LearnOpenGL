#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 coord;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);

	void Bind()const;
	void UnBind()const;
	void Delete()const;
};

