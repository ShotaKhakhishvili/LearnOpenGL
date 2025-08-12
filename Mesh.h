#pragma once

#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

struct MeshParameters
{
	std::string meshName;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};

