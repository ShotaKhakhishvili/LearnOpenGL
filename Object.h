#pragma once

#include "Mesh.h"
#include <unordered_map>
#include <memory>

class Object
{
private:
	static std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
	static std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;
	static std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;

	std::vector<std::shared_ptr<Texture>> textures;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Mesh> mesh;

	glm::vec3 translation{ 1.0f,0.0f,0.0f };
	glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::mat4 modelMat;

public:
	Object(const char* meshName, const char* shaderName, const std::vector<TextureParameters>& textureParameters);

	void Draw(Camera& camera);

	static void MakeShader(const char* shaderName, const char* vertShader, const char* fragShader, bool replaceIfAlreadyExists = true);

	bool SetupObject(const char* meshName, const char* shaderName, const std::vector<TextureParameters>& textureParameters);

	void SetMesh(const char* meshName);
	bool SetShaderProgram(const char* shaderName);
	void SetTextures(const std::vector<TextureParameters>& textureNames);

	void RefreshMatrix();

	std::shared_ptr<Shader> GetShader() { return shader; };
};

