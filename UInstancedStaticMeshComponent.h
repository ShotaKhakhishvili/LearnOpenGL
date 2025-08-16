#pragma once

#include "UStaticMeshComponent.h"

class UInstancedStaticMeshComponent : public USceneComponent
{
    std::shared_ptr<UModel> model;
    std::vector<glm::mat4> localInstanceMatrices;
    std::vector<glm::mat4> worldInstanceMatrices;

    bool dirtyInstanceMatrices = true;

    void Draw(UCamera& camera) override;
    void RefreshMatrices();

public:
    UInstancedStaticMeshComponent(const std::string& meshName, const std::string& materialName);

    void AddInstance(const Transform& newInstTransform);
    void RemoveInstance(const unsigned int instIndex);

    void OnTransformChange() override;
};