#pragma once

#include "UObject.h"
#include <vector>
#include "glm/glm.hpp"

class UActorComponent;
class USceneComponent;
struct Transform;

class AActor : public UObject
{
	AActor* parent;
	std::vector<AActor*> children;

	USceneComponent* rootComponent;
	std::vector<UActorComponent*> actorComponents;

public:
	AActor(const Transform& transform);

	const std::vector<UActorComponent*>& GetChildActorComponents() const;

	void DettachActorComponent(UActorComponent* compToDettach);
	void AttachActorComponent(UActorComponent* compToAttach);

	USceneComponent* GetRoot() const;

	void SetActorRotation(glm::vec3 newRot);
	void SetActorRotationInQuat(glm::quat newRot);
	void OffsetActorRotation(glm::vec3 deltaRot);
	void SetActorLocation(glm::vec3 newPos);
	void OffsetActorLocation(glm::vec3 deltaPos);
	void SetActorScale(glm::vec3 newScale);
	void OffsetActorScale(glm::vec3 deltaScale);

	glm::vec3 GetActorRotation()const;
	glm::quat GetActorRotationInQuat()const;
	glm::vec3 GetActorLocation()const;
	glm::vec3 GetActorScale()const;
	glm::mat4 GetActorMatrix();

	Transform GetActorTransform()const;
};