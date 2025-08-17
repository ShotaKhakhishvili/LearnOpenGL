#pragma once

#include "UActorComponent.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class UCamera;
class UWorld;

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

class USceneComponent : public UActorComponent
{
	glm::vec3 position{ 0.0f,0.0f,0.0f };
	glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::mat4 mat;

	bool dirtyMatrix = false;

	USceneComponent* parent;
	std::vector<USceneComponent*> children;

	virtual void Draw(UCamera& camera);
	void RefreshMatrix();

	friend class UWorld;

public:

	USceneComponent();
	USceneComponent(const Transform& transform);
	~USceneComponent();

	USceneComponent* GetParent();
	const std::vector<USceneComponent*>& GetChildren();

	void SetRotation(glm::vec3 newRot);
	void SetRotationInQuat(glm::quat newRot);
	void OffsetRotation(glm::vec3 deltaRot);
	void SetLocation(glm::vec3 newPos);
	void OffsetLocation(glm::vec3 deltaPos);
	void SetScale(glm::vec3 newScale);
	void OffsetScale(glm::vec3 deltaScale);

	glm::vec3 GetRotation()const;
	glm::quat GetRotationInQuat()const;
	glm::vec3 GetLocation()const;
	glm::vec3 GetScale()const;
	glm::mat4 GetMatrix();
	glm::mat4 GetWorldMatrix();

	Transform GetTransform()const;
	virtual void OnTransformChange();

	bool SetParent(USceneComponent* newParent);
	bool AddChild(USceneComponent* child);
};

