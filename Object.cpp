#include "Object.h"
#include "Data.h"
#include "FuncLib.h"

Object::Object(const std::string& meshName, const std::string& materialName)
{
	model = std::make_shared<Model>(meshName, materialName);
	RefreshMatrix();
}

void Object::Draw(Camera& camera)
{
	model->ActivateModel(camera);

	glUniformMatrix4fv(glGetUniformLocation(model->material->shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glDrawElements(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0);
}

void Object::RefreshMatrix()
{
	glm::mat4 mat_translation = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 mat_rotation = glm::toMat4(rotation);
	glm::mat4 mat_scale = glm::scale(glm::mat4(1.0f), scale);

	modelMat = mat_translation * mat_rotation * mat_scale;
}

void Object::SetRotation(glm::vec3 newRot)		{	rotation = glm::quat(glm::radians(newRot));					RefreshMatrix(); }
void Object::AddRotation(glm::vec3 deltaRot)	{	rotation = glm::quat(glm::radians(deltaRot)) * rotation;	RefreshMatrix(); }
void Object::SetPosition(glm::vec3 newPos)		{	translation = newPos;										RefreshMatrix(); }
void Object::AddPosition(glm::vec3 deltaPos)	{	translation += deltaPos;									RefreshMatrix(); }
void Object::SetScale(glm::vec3 newScale)		{	scale = newScale;											RefreshMatrix(); }
void Object::AddScale(glm::vec3 deltaScale)		{	scale += deltaScale;										RefreshMatrix(); }

glm::vec3 Object::GetPosition()const	{	return translation;											}
glm::vec3 Object::GetRotation()const	{	return glm::degrees(glm::eulerAngles(rotation));			}
glm::vec3 Object::GetScale()const		{	return scale;												}

Transform Object::GetTransform()const	{ return Transform{ GetPosition(), GetRotation(), GetScale()};	}
