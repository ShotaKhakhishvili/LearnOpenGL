#pragma once

#include "AActor.h"
#include "UObject.h"

class UActorComponent : public UObject
{
	AActor* owner = nullptr;
	bool bIsActive;
	bool bIsTicking;

	bool bPendingKill;

public:
	UActorComponent();
	~UActorComponent();

	AActor* GetOwner() const;

	void SetActive(bool bVal);
	bool IsActive() const;
	void SetTicking(bool bVal);
	bool IsTicking() const;

	void RegisterComponent(AActor* newOwner);
	void UnRegisterComponent();

	void DestroyComponent();

	virtual void OnComponentBeginPlay();
	virtual void OnComponentEndPlay();
	virtual void OnComponentTick();
};

