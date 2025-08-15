#pragma once

#include "UObject.h"
#include "VAO.h"
#include "EBO.h"
#include "UTexture.h"

struct MeshParameters
{
	std::string meshName;
};

class UStaticMesh 
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VAO VAO;

	UStaticMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};

