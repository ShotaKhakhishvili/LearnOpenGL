#include "UObject.h"

std::vector<UObject*> UObject::GObjectArray;
std::vector<UObject*> UObject::roots;
unsigned int UObject::iObjectCount = 0;

UObject::UObject()
	: name("Object " + std::to_string(iObjectCount++)), bMarkedForGC(false), bPendingToKill(false)
{
	GObjectArray.push_back(this);
}

UObject::~UObject()
{
	auto it = std::find(GObjectArray.begin(), GObjectArray.end(), this);
	if (it != GObjectArray.end()) {
		*it = GObjectArray.back();
		GObjectArray.pop_back();
	}
}

void UObject::AddRoot(UObject* newRoot)
{
    roots.push_back(newRoot);
}

void UObject::RemoveRoot(UObject* rootToRem)
{
    auto it = std::find(roots.begin(), roots.end(), rootToRem);
    if (it != roots.end())
    {
        *it = roots.back();
        roots.pop_back();
    }
}

void UObject::CollectGarbage() {
    // 1. Clear marks
    for (auto* obj : GObjectArray) {
        obj->bMarkedForGC = false;
    }

    // 2. Mark phase using BFS
    std::vector<UObject*> stack = roots;
    while (!stack.empty()) {
        UObject* current = stack.back();
        stack.pop_back();
        if (!current || current->bMarkedForGC) continue;
        current->bMarkedForGC = true;

        std::vector<UObject*> refs;
        current->CollectReferences(refs);
        for (auto* ref : refs)
            stack.push_back(ref);
    }

    // 3. Sweep phase
    for (auto it = GObjectArray.begin(); it != GObjectArray.end();) {
        if (!(*it)->bMarkedForGC) {
            delete* it;
            it = GObjectArray.erase(it);
        }
        else {
            ++it;
        }
    }
}