#pragma once

#include "Model.h"
#include "Component.h"
#include <unordered_map>
#include <memory>

class MeshComponent : public Component
{
private:
	std::shared_ptr<Model> model;

public:

	MeshComponent(const std::string& meshName, const std::string& materialName);

	void Draw(Camera& camera);
};
