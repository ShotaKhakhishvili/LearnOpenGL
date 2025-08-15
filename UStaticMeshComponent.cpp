#include "UStaticMeshComponent.h"
#include "Data.h"
#include "FuncLib.h"
#include "UCamera.h"

UStaticMeshComponent::UStaticMeshComponent(const std::string& meshName, const std::string& materialName)
{
	model = std::make_shared<UModel>(meshName, materialName);
	RefreshMatrix();
}

void UStaticMeshComponent::Draw(UCamera& camera)
{
	model->ActivateModel(camera);

	glUniformMatrix4fv(glGetUniformLocation(model->material->shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(GetWorldMatrix()));
	glDrawElements(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0);
}
