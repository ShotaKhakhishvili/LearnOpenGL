#include "UWorld.h"
#include "USceneComponent.h"
#include <iostream>

void UWorld::DestroyActor(AActor* actor)
{
    auto it = std::find(GObjectArray.begin(), GObjectArray.end(), actor);
    if (it != GObjectArray.end())
    {
        *it = GObjectArray.back();
        GObjectArray.pop_back();
    }
    auto itActor = std::find(actors.begin(), actors.end(), actor);
    if (itActor != actors.end())
    {
        *itActor = actors.back();
        actors.pop_back();
    }

    actor->bPendingToKill = true;
}

void UWorld::Tick(UCamera& camera)
{
    static int i = 0;
    for (auto* object : GObjectArray)
    {
        if (USceneComponent* sceneComp = dynamic_cast<USceneComponent*>(object))
        {
            sceneComp->Draw(camera);
            std::cout << i++ << '\n';
        }
    }
    std::cout << "---------" << '\n';
}

void UWorld::RegisterObject(UObject* obj)
{
	GObjectArray.push_back(obj);
}

void UWorld::UnregisterObject(UObject* obj)
{
	auto it = std::find(GObjectArray.begin(), GObjectArray.end(), obj);
	if (it != GObjectArray.end()) {
		*it = GObjectArray.back();
		GObjectArray.pop_back();
	}
}

void UWorld::CollectGarbage()
{
    // 1. Clear marks
    for (auto* obj : GObjectArray) {
        obj->bMarkedForGC = false;
    }

    // 2. Mark phase starting from all actors in the world
    std::vector<UObject*> stack(actors.begin(), actors.end());
    while (!stack.empty()) {
        UObject* current = stack.back();
        stack.pop_back();
        if (!current || current->bMarkedForGC) continue;
        current->bMarkedForGC = true;

        std::vector<UObject*> refs;
        current->CollectReferences(refs);
        for (auto* ref : refs) {
            if (ref && !ref->bMarkedForGC)
                stack.push_back(ref);
        }
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
