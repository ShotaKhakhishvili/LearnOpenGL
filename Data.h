#pragma once
#include "Mesh.h"
#include "Material.h"
#include <vector>
#include <unordered_map>

namespace Data
{
	extern std::unordered_map<std::string, TextureParameters> textureParameters;
	extern std::unordered_map<std::string, ShaderParameters> shaderParameters;
	extern std::unordered_map<std::string, MaterialParameters> materialParameters;
	extern std::unordered_map<std::string, MeshParameters> meshParameters;

	extern std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
	extern std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;
	extern std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;

	extern std::shared_ptr<Shader> MakeShader(const std::string& shaderName, const ShaderParameters& parameters, bool replaceIfAlreadyExists = true);

	extern std::shared_ptr<Mesh> GetMesh(const std::string& meshName);
	extern std::shared_ptr<Shader> GetShader(const std::string& shaderName);
	extern std::shared_ptr<Texture> GetTexture(const std::string& textureName);
	extern std::shared_ptr<Material> GetMaterial(const std::string& materialName);
	extern std::vector<std::shared_ptr<Texture>> GetTextures(const std::vector<std::string>& textureNames);
};