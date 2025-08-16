#pragma once

#include <vector>
#include <string>

class UWorld;

class UObject
{
private:

	const std::string name;
	UWorld* world;
	bool bMarkedForGC;
	bool bPendingToKill;

	friend class UWorld;

public:
	UObject();
	virtual ~UObject();

	void SetWorld(UWorld* newWorld);
	UWorld* GetWorld() const;

	virtual void CollectReferences(std::vector<UObject*>& outRefs) {}
};

