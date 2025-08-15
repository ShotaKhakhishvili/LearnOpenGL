#pragma once
#include <vector>

class UActorComponent;
class USceneComponent;
struct Transform;

class AActor
{
	AActor* parent;
	std::vector<AActor*> children;

	USceneComponent* rootComponent;
	std::vector<UActorComponent*> actorComponents;

public:
	AActor(const Transform& transform);

	const std::vector<UActorComponent*>& GetChildActorComponents() const;
	void DettachActorComponent(const UActorComponent* compToDettach);
	void AttachActorComponent(const UActorComponent* compToAttach);

};

