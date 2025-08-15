#include "UStaticMesh.h"

UStaticMesh::UStaticMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
{
	this->vertices = vertices;
	this->indices = indices;

	VAO.Bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(GL_FLOAT)));

	VAO.UnBind();
	VBO.UnBind();
	EBO.UnBind();
}

