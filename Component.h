#pragma once

#include "Camera.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

class Component
{
	glm::vec3 translation{ 0.0f,0.0f,0.0f };
	glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::mat4 mat;

	bool dirtyMatrix = false;

	Component* parent;
	std::vector<Component*> children;

public:

	Component();
	Component(const Transform& transform);

	Component* GetParent();
	std::vector<Component*> GetChildren();

	bool SetParent(Component* newParent);
	bool AddChild(Component* child);

	void RefreshMatrix();

	void SetRotation(glm::vec3 newRot);
	void AddRotation(glm::vec3 deltaRot);
	void SetPosition(glm::vec3 newPos);
	void AddPosition(glm::vec3 deltaPos);
	void SetScale(glm::vec3 newScale);
	void AddScale(glm::vec3 deltaScale);

	virtual void OnTransformChange();

	glm::vec3 GetRotation()const;
	glm::vec3 GetPosition()const;
	glm::vec3 GetScale()const;
	glm::mat4 GetMatrix();
	glm::mat4 GetWorldMatrix();

	Transform GetTransform()const;
};

