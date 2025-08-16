#include "UObject.h"
#include "UWorld.h"

UObject::UObject()
	: bMarkedForGC(false), bPendingToKill(false)
{
}

UObject::~UObject()
{
    if(world)
        world->UnregisterObject(this);
}

void UObject::SetWorld(UWorld* newWorld)
{
    if (newWorld == world)
        return;

    if (world != NULL)
        world->UnregisterObject(this);

    world = newWorld;
    
    if(world != NULL)
    {
        world->RegisterObject(this);
    }
}

UWorld* UObject::GetWorld() const { return world; }