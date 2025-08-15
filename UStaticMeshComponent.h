#pragma once

#include "UModel.h"
#include "USceneComponent.h"
#include <unordered_map>
#include <memory>

class UStaticMeshComponent : public USceneComponent
{
private:
	std::shared_ptr<UModel> model;

public:

	UStaticMeshComponent(const std::string& meshName, const std::string& materialName);

	void Draw(UCamera& camera) override;
};
