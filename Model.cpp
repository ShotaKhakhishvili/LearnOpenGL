#include "Model.h"
#include "Data.h"

Model::Model(const std::string& meshName, const std::string& materialName)
{
	SetupModel(meshName, materialName);
}

void Model::SetMesh(const std::string& meshName)
{
	mesh = Data::GetMesh(meshName);
}

void Model::SetMaterial(const std::string& materialName)
{
	material = Data::GetMaterial(materialName);
}

void Model::SetupModel(const std::string& meshName, const std::string& materialName)
{
	SetMaterial(materialName);
	SetMesh(meshName);
}

void Model::ActivateModel(Camera& camera)
{
	material->shader->Activate();
	mesh->VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < material->textures.size(); i++)
	{
		std::string num;
		std::string type = material->textures[i]->type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else
		{
			num = std::to_string(numSpecular++);
		}
		material->textures[i]->TexUnit(*(material->shader), (type + num).c_str(), i);
		material->textures[i]->Bind();
	}

	glUniform3f(glGetUniformLocation(material->shader->ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(*(material->shader), "camMat");
}
