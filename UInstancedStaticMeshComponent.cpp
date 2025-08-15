#include "UInstancedStaticMeshComponent.h"

UInstancedStaticMeshComponent::UInstancedStaticMeshComponent(const std::string& meshName, const std::string& materialName)
{
	model = std::make_shared<UModel>(meshName, materialName);
}

void UInstancedStaticMeshComponent::Draw(UCamera& camera)
{
    model->ActivateModel(camera);

    GLuint modelLoc = glGetUniformLocation(model->material->shader->ID, "model");

    if (dirtyInstanceMatrices) 
        RefreshMatrices();

    for (const auto& mat : worldInstanceMatrices)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
        glDrawElements(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void UInstancedStaticMeshComponent::AddInstance(const Transform& newInstTransform)
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), newInstTransform.Position);
    glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(newInstTransform.Rotation)));
    glm::mat4 size = glm::scale(glm::mat4(1.0f), newInstTransform.Scale);

    localInstanceMatrices.push_back(translate * rotation * size);
}


void UInstancedStaticMeshComponent::RemoveInstance(const unsigned int instIndex)
{
    if (instIndex < localInstanceMatrices.size()) {
        std::swap(localInstanceMatrices[instIndex], localInstanceMatrices.back());
        localInstanceMatrices.pop_back();
    }
}

void UInstancedStaticMeshComponent::OnTransformChange()
{
    USceneComponent::OnTransformChange();
    dirtyInstanceMatrices = true;
}


void UInstancedStaticMeshComponent::RefreshMatrices()
{
    worldInstanceMatrices.resize(localInstanceMatrices.size());
    glm::mat4 baseWorld = GetWorldMatrix();

    for (size_t i = 0; i < localInstanceMatrices.size(); ++i)
    {
        worldInstanceMatrices[i] = baseWorld * localInstanceMatrices[i];
    }
    dirtyInstanceMatrices = false;
}
