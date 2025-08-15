#pragma once

#include "UStaticMeshComponent.h"

class UInstancedStaticMeshComponent : public USceneComponent
{
    std::shared_ptr<UModel> model;
    std::vector<glm::mat4> localInstanceMatrices;
    std::vector<glm::mat4> worldInstanceMatrices;

    bool dirtyInstanceMatrices = true;

public:
    UInstancedStaticMeshComponent(const std::string& meshName, const std::string& materialName);

    void Draw(UCamera& camera) override;

    void AddInstance(const Transform& newInstTransform);
    void RemoveInstance(const unsigned int instIndex);

    void OnTransformChange() override;
    void RefreshMatrices();
};