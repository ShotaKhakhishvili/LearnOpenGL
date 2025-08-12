#pragma once

#include "Object.h"

class InstancedObject
{
public:
    std::shared_ptr<Model> model;
    std::vector<glm::mat4> instanceMatrices;

    InstancedObject(const std::string& meshName, const std::string& materialName);

    void DrawInstances(Camera& camera);

    void AddInstance(const Transform& newInstTransform);
    void RemoveInstance(const unsigned int instIndex);
};