#include "Object.h"
#include "FuncLib.h"

std::unordered_map<std::string, std::shared_ptr<Mesh>> Object::loadedMeshes;
std::unordered_map<std::string, std::shared_ptr<Shader>> Object::loadedShaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> Object::loadedTextures;

Object::Object(const char* meshName, const char* shaderName, const std::vector<TextureParameters>& textureParameters)
{
	SetupObject(meshName, shaderName, textureParameters);
	RefreshMatrix();
}

void Object::Draw(Camera& camera)
{
	mesh->Draw(*shader, camera, modelMat);
}

void Object::MakeShader(const char* shaderName, const char* vertShader, const char* fragShader, bool replaceIfAlreadyExists)
{
	if (loadedShaders.count(shaderName) && !replaceIfAlreadyExists) return;

	loadedShaders.emplace(shaderName,std::make_shared<Shader>(vertShader, fragShader));
}

bool Object::SetupObject(const char* meshName, const char* shaderName, const std::vector<TextureParameters>& textureParameters)
{
	if (!SetShaderProgram(shaderName))return false;;
	SetTextures(textureParameters);
	SetMesh(meshName);

	return true;
}

void Object::SetMesh(const char* meshName)
{
	auto it = loadedMeshes.find(meshName);
	if (it != loadedMeshes.end())
	{
		mesh = it->second;
	}
	else
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		ReadFromObjIntoVectors(meshName, vertices, indices);
		mesh = std::make_shared<Mesh>(vertices, indices, textures);
		loadedMeshes.emplace(meshName, mesh);
	}
}

bool Object::SetShaderProgram(const char* shaderName)
{
	auto it = loadedShaders.find(shaderName);
	if (it == loadedShaders.end()) return false;
	shader = it->second;
	return true;
}

void Object::SetTextures(const std::vector<TextureParameters>& textureParameters)
{
	for (const auto& params : textureParameters)
	{
		auto it = loadedTextures.find(params.image);
		if (it != loadedTextures.end())
		{
			textures.push_back(it->second);
		}
		else
		{
			auto tex = std::make_shared<Texture>(
				params.image,
				params.texType,
				params.slot,
				params.format,
				params.pixelType
			);
			loadedTextures.emplace(params.image, tex);
			textures.push_back(tex);
		}
	}
}

void Object::RefreshMatrix()
{
	glm::mat4 mat_translation = glm::translate(glm::mat4(1.0f), translation);

	glm::mat4 mat_rotation = glm::toMat4(rotation);

	glm::mat4 mat_scale = glm::scale(glm::mat4(1.0f), scale);

	modelMat = mat_translation * mat_rotation * mat_scale;
}

