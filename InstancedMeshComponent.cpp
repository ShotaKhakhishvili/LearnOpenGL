#include "InstancedMeshComponent.h"

InstancedMeshComponent::InstancedMeshComponent(const std::string& meshName, const std::string& materialName)
{
	model = std::make_shared<Model>(meshName, materialName);
}

void InstancedMeshComponent::DrawInstances(Camera& camera)
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

void InstancedMeshComponent::AddInstance(const Transform& newInstTransform)
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), newInstTransform.Position);
    glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(newInstTransform.Rotation)));
    glm::mat4 size = glm::scale(glm::mat4(1.0f), newInstTransform.Scale);

    localInstanceMatrices.push_back(translate * rotation * size);
}


void InstancedMeshComponent::RemoveInstance(const unsigned int instIndex)
{
    if (instIndex < localInstanceMatrices.size()) {
        std::swap(localInstanceMatrices[instIndex], localInstanceMatrices.back());
        localInstanceMatrices.pop_back();
    }
}

void InstancedMeshComponent::OnTransformChange()
{
    Component::OnTransformChange();
    dirtyInstanceMatrices = true;
}

void InstancedMeshComponent::RefreshMatrices()
{
    worldInstanceMatrices.resize(localInstanceMatrices.size());
    glm::mat4 baseWorld = GetWorldMatrix();

    for (size_t i = 0; i < localInstanceMatrices.size(); ++i)
    {
        worldInstanceMatrices[i] = baseWorld * localInstanceMatrices[i];
    }
    dirtyInstanceMatrices = false;
}
