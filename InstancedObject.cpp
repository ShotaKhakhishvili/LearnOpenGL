#include "InstancedObject.h"

InstancedObject::InstancedObject(const std::string& meshName, const std::string& materialName)
{
	model = std::make_shared<Model>(meshName, materialName);
}

void InstancedObject::DrawInstances(Camera& camera)
{
    model->ActivateModel(camera);

    GLuint modelLoc = glGetUniformLocation(model->material->shader->ID, "model");

    for (const auto& mat : instanceMatrices)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
        glDrawElements(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void InstancedObject::AddInstance(const Transform& newInstTransform)
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), newInstTransform.Position);
    glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(newInstTransform.Rotation)));
    glm::mat4 size = glm::scale(glm::mat4(1.0f), newInstTransform.Scale);

    instanceMatrices.push_back(translate * rotation * size);
}


void InstancedObject::RemoveInstance(const unsigned int instIndex)
{
    if (instIndex < instanceMatrices.size()) {
        std::swap(instanceMatrices[instIndex], instanceMatrices.back());
        instanceMatrices.pop_back();
    }
}
