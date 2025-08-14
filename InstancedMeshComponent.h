#pragma once

#include "MeshComponent.h"

class InstancedMeshComponent : public Component
{
    std::shared_ptr<Model> model;
    std::vector<glm::mat4> localInstanceMatrices;
    std::vector<glm::mat4> worldInstanceMatrices;

    bool dirtyInstanceMatrices = true;

public:
    InstancedMeshComponent(const std::string& meshName, const std::string& materialName);

    void DrawInstances(Camera& camera);

    void AddInstance(const Transform& newInstTransform);
    void RemoveInstance(const unsigned int instIndex);

    void OnTransformChange() override;
    void RefreshMatrices();
};