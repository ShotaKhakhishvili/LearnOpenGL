#pragma once

#include "UObject.h"
#include "URenderer.h"
#include "AActor.h"
#include "UCamera.h"
#include <memory>

class UWorld
{
private:
    std::vector<UObject*> GObjectArray; // all objects in this world
    std::vector<AActor*> actors;        // objects that should never be GC'd
    UCamera* mainCamera;
    unsigned int iObjectCount = 0;

public:

    template<typename T, typename... Args>
    T* SpawnActor(Args&&... args);
    void DestroyActor(AActor* actor);

    template<typename T>
    T* GetActorOfClass();

    template<typename T>
    std::vector<T*> GetAllActorsOfClass();

    void Tick(UCamera& camera);

    void RegisterObject(UObject* obj);
    void UnregisterObject(UObject* obj);

    void CollectGarbage();
};

template<typename T, typename ...Args>
inline T* UWorld::SpawnActor(Args && ...args)
{
    static_assert(std::is_base_of<AActor, T>::value, "You can only spawn a class derived from AActor");

    std::unique_ptr<T> newObj = std::make_unique<T>(std::forward<Args>(args)...);
    T* rawPtr = newObj.get();

    AActor* rawAsActor = dynamic_cast<AActor*>(rawPtr);
    
    actors.push_back(rawPtr);
    RegisterObject(rawPtr);
    RegisterObject(rawPtr->GetRoot());

    newObj.release();
    return rawPtr;
}

template<typename T>
inline T* UWorld::GetActorOfClass()
{
    for (const auto& actor : actors)
    {
        if (T* casted = dynamic_cast<T*>(actor))
            return actor;
    }
    return nullptr;
}

template<typename T>
inline std::vector<T*> UWorld::GetAllActorsOfClass()
{
    std::vector<T*> result;
    for (const auto& actor : actors)
    {
        if (T* casted = dynamic_cast<T*>(actor.get()))
            result.push_back(casted);
    }
    return result;
}

