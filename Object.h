#pragma once

#include "Model.h"
#include <unordered_map>
#include <memory>

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

class Object
{
private:
	std::shared_ptr<Model> model;

	glm::vec3 translation{ 1.0f,0.0f,0.0f };
	glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::mat4 modelMat;

public:
	Object(const std::string& meshName, const std::string& materialName);

	void Draw(Camera& camera);

	void RefreshMatrix();

	void SetRotation(glm::vec3 newRot);
	void AddRotation(glm::vec3 deltaRot);
	void SetPosition(glm::vec3 newPos);
	void AddPosition(glm::vec3 deltaPos);
	void SetScale(glm::vec3 newScale);
	void AddScale(glm::vec3 deltaScale);

	glm::vec3 GetRotation()const;
	glm::vec3 GetPosition()const;
	glm::vec3 GetScale()const;
	Transform GetTransform()const;
};
