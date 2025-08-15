#pragma once

#include "AActor.h"
#include <vector>
#include <string>

class UObject
{
private:

	static std::vector<UObject*> GObjectArray;
	static std::vector<UObject*> roots;
	static unsigned int iObjectCount;

	static void AddRoot(UObject* newRoot);	
	static void RemoveRoot(UObject* rootToRem);

	const std::string name;
	bool bMarkedForGC;
	bool bPendingToKill;

	friend class AActor;

public:
	UObject();

	static void CollectGarbage();

	virtual void CollectReferences(std::vector<UObject*>& outRefs) {}
	virtual ~UObject();
};

