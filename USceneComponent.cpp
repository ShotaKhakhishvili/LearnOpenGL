#include "USceneComponent.h"

USceneComponent::USceneComponent()
{
	RefreshMatrix();
}

USceneComponent::USceneComponent(const Transform& transform)
{
	position = transform.Position;
	rotation = glm::quat(glm::radians(transform.Rotation));
	scale = transform.Scale;

	RefreshMatrix();
}

USceneComponent::~USceneComponent()
{
	for (auto* child : children)
	{
		child->parent = nullptr;
		delete child; // will call child's destructor, which deletes its own children
	}
	children.clear();
	parent = nullptr;
}

USceneComponent* USceneComponent::GetParent(){ return parent; }
const std::vector<USceneComponent*>& USceneComponent::GetChildren() { return children;  }

bool USceneComponent::SetParent(USceneComponent* newParent)
{
	// Doesn't do anything if new parent is itself or the current parent
	if (newParent == this || parent == newParent)
	{
		return false;
	}
	
	for (USceneComponent* currParent = newParent; currParent != NULL; currParent = currParent->parent)
	{
		if (currParent == this)
			return false;
	}

	if (parent != NULL)
	{
		auto& siblings = parent->children;

		siblings.erase(
			std::remove(siblings.begin(), siblings.end(), this),
			siblings.end()
		);
	}

	// Sets the new parent as the current one and adds 
	parent = newParent;

	if(parent != NULL)
		parent->children.push_back(this);

	return true;
}

bool USceneComponent::AddChild(USceneComponent* child)
{
	return child->SetParent(this);
}

void USceneComponent::Draw(UCamera& camera)
{
}

void USceneComponent::RefreshMatrix()
{
	glm::mat4 mat_translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 mat_rotation = glm::toMat4(rotation);
	glm::mat4 mat_scale = glm::scale(glm::mat4(1.0f), scale);

	mat = mat_translation * mat_rotation * mat_scale;
	dirtyMatrix = false;
}

void USceneComponent::SetRotation(glm::vec3 newRot)			{ rotation = glm::quat(glm::radians(newRot));					OnTransformChange(); }
void USceneComponent::SetRotationInQuat(glm::quat newRot)	{ rotation = newRot;											OnTransformChange(); }
void USceneComponent::OffsetRotation(glm::vec3 deltaRot)	{ rotation = glm::quat(glm::radians(deltaRot)) * rotation;		OnTransformChange(); }
void USceneComponent::SetLocation(glm::vec3 newPos)			{ position = newPos;											OnTransformChange(); }
void USceneComponent::OffsetLocation(glm::vec3 deltaPos)	{ position += deltaPos;											OnTransformChange(); }
void USceneComponent::SetScale(glm::vec3 newScale)			{ scale = newScale;												OnTransformChange(); }
void USceneComponent::OffsetScale(glm::vec3 deltaScale)		{ scale += deltaScale;											OnTransformChange(); }

inline void USceneComponent::OnTransformChange() { dirtyMatrix = true; }

glm::vec3 USceneComponent::GetLocation()const		{ return position;									}
glm::vec3 USceneComponent::GetRotation()const		{ return glm::degrees(glm::eulerAngles(rotation));	}
glm::quat USceneComponent::GetRotationInQuat()const { return rotation;									}
glm::vec3 USceneComponent::GetScale()const			{ return scale;										}
glm::mat4 USceneComponent::GetMatrix()				{ if (dirtyMatrix) RefreshMatrix(); return mat;		}
glm::mat4 USceneComponent::GetWorldMatrix()
{ 
	if (dirtyMatrix) 
		RefreshMatrix(); 
	if(parent)
		return parent->GetWorldMatrix() * mat;
	return mat;
}

Transform USceneComponent::GetTransform()const { return Transform{ GetLocation(), GetRotation(), GetScale() }; }