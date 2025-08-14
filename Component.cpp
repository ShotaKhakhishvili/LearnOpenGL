#include "Component.h"

Component::Component()
{
	RefreshMatrix();
}

Component::Component(const Transform& transform)
{
	translation = transform.Position;
	rotation = glm::quat(glm::radians(transform.Rotation));
	scale = transform.Scale;

	RefreshMatrix();
}

Component* Component::GetParent(){ return parent; }
std::vector<Component*> Component::GetChildren() { return children;  }

bool Component::SetParent(Component* newParent)
{
	// Doesn't do anything if new parent is itself or the current parent
	if (newParent == this || parent == newParent)
	{
		return false;
	}
	
	for (Component* currParent = newParent; currParent != NULL; currParent = currParent->parent)
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

bool Component::AddChild(Component* child)
{
	return child->SetParent(this);
}

void Component::RefreshMatrix()
{
	glm::mat4 mat_translation = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 mat_rotation = glm::toMat4(rotation);
	glm::mat4 mat_scale = glm::scale(glm::mat4(1.0f), scale);

	mat = mat_translation * mat_rotation * mat_scale;
	dirtyMatrix = false;
}

void Component::SetRotation(glm::vec3 newRot) { rotation = glm::quat(glm::radians(newRot));					OnTransformChange(); }
void Component::AddRotation(glm::vec3 deltaRot) { rotation = glm::quat(glm::radians(deltaRot)) * rotation;	OnTransformChange(); }
void Component::SetPosition(glm::vec3 newPos) { translation = newPos;										OnTransformChange(); }
void Component::AddPosition(glm::vec3 deltaPos) { translation += deltaPos;									OnTransformChange(); }
void Component::SetScale(glm::vec3 newScale) { scale = newScale;											OnTransformChange(); }
void Component::AddScale(glm::vec3 deltaScale) { scale += deltaScale;										OnTransformChange(); }

inline void Component::OnTransformChange() { dirtyMatrix = true; }

glm::vec3 Component::GetPosition()const { return translation;								}
glm::vec3 Component::GetRotation()const { return glm::degrees(glm::eulerAngles(rotation));	}
glm::vec3 Component::GetScale()const	{ return scale;										}
glm::mat4 Component::GetMatrix()		{ if (dirtyMatrix) RefreshMatrix(); return mat;		}

glm::mat4 Component::GetWorldMatrix()	
{ 
	if (dirtyMatrix) 
		RefreshMatrix(); 
	if(parent)
		return parent->GetWorldMatrix() * mat;
	return mat;
}

Transform Component::GetTransform()const { return Transform{ GetPosition(), GetRotation(), GetScale() }; }