#include "UActorComponent.h"

UActorComponent::UActorComponent()
	: owner(nullptr), bIsActive(true), bIsTicking(false), bPendingKill(false)
{
}

UActorComponent::~UActorComponent()
{
	if (owner)
		owner->DettachActorComponent(this);
	OnComponentEndPlay();
}

AActor* UActorComponent::GetOwner() const	{ return owner; }
bool UActorComponent::IsActive() const		{ return bIsActive; }
bool UActorComponent::IsTicking() const		{ return bIsTicking; }
void UActorComponent::SetTicking(bool bVal) { bIsTicking = bVal; }
void UActorComponent::SetActive(bool bVal)	{ bIsActive = bVal; }

void UActorComponent::RegisterComponent(AActor* newOwner)
{
	if (owner)
	{
		owner->DettachActorComponent(this);
	}

	owner = newOwner;
	owner->AttachActorComponent(this);
}

void UActorComponent::UnRegisterComponent()
{
	if (owner)
	{
		owner->DettachActorComponent(this);
	}
	owner = nullptr;
}

void UActorComponent::DestroyComponent()
{
	if (owner)
	{
		UnRegisterComponent();
	}

	bPendingKill = true;
}

void UActorComponent::OnComponentBeginPlay()
{
}

void UActorComponent::OnComponentEndPlay()
{
}

void UActorComponent::OnComponentTick()
{
}

