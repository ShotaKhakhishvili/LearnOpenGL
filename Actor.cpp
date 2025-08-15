#include "AActor.h"
#include "USceneComponent.h"

AActor::AActor(const Transform& transform)
	: parent(nullptr), children(), actorComponents()
{
	rootComponent = new USceneComponent(transform);
}

const std::vector<UActorComponent*>& AActor::GetChildActorComponents() const
{
	return actorComponents;
}

void AActor::DettachActorComponent(const UActorComponent* compToDettach)
{
}

void AActor::AttachActorComponent(const UActorComponent* compToAttach)
{
}
