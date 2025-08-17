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

void AActor::DettachActorComponent(UActorComponent* compToDettach)
{
}

void AActor::AttachActorComponent(UActorComponent* compToAttach)
{
	if (USceneComponent* sceneComp = dynamic_cast<USceneComponent*>(compToAttach))
	{
		sceneComp->SetParent(rootComponent);
	}
	else
	{
		actorComponents.push_back(compToAttach);
	}
}

USceneComponent* AActor::GetRoot() const { return rootComponent; }

void AActor::SetActorRotation(glm::vec3 newRot)			{ rootComponent->SetRotation(newRot);		}
void AActor::SetActorRotationInQuat(glm::quat newRot)	{ rootComponent->SetRotationInQuat(newRot); }
void AActor::OffsetActorRotation(glm::vec3 deltaRot)	{ rootComponent->OffsetRotation(deltaRot);	}
void AActor::SetActorLocation(glm::vec3 newPos)			{ rootComponent->SetLocation(newPos);		}
void AActor::OffsetActorLocation(glm::vec3 deltaPos)	{ rootComponent->OffsetLocation(deltaPos);	}
void AActor::SetActorScale(glm::vec3 newScale)			{ rootComponent->SetScale(newScale);		}
void AActor::OffsetActorScale(glm::vec3 deltaScale)		{ rootComponent->OffsetScale(deltaScale);	}

glm::vec3 AActor::GetActorRotation() const			{ return rootComponent->GetRotation();			}
glm::quat AActor::GetActorRotationInQuat() const	{ return rootComponent->GetRotationInQuat();	}
glm::vec3 AActor::GetActorLocation() const			{ return rootComponent->GetLocation();			}
glm::vec3 AActor::GetActorScale() const				{ return rootComponent->GetScale();				}
glm::mat4 AActor::GetActorMatrix()					{ return rootComponent->GetMatrix();			}
Transform AActor::GetActorTransform() const			{ return rootComponent->GetTransform();			}
