#include "Data.h"
#include "FuncLib.h"
#include <stdexcept>

namespace Data
{
	std::unordered_map<std::string, TextureParameters> textureParameters = 
	{
		{"Sword_BaseColor", TextureParameters{ "Sword_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE }},
		{"Sword_Roughness", TextureParameters{ "Sword_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE }},
		{"Grass_BaseColor", TextureParameters{ "Grass.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE }},
		{"Plank_BaseColor", TextureParameters{ "Planks_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE }},
		{"Plank_Roughness", TextureParameters{ "Planks_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE }},
	};

	std::unordered_map<std::string, MaterialParameters> materialParameters =
	{
		{"Sword", MaterialParameters{"Default",	std::vector<std::string>{"Sword_BaseColor", "Sword_Roughness"}}},
		{"Grass", MaterialParameters{"Default",	std::vector<std::string>{"Grass_BaseColor", "Plank_Roughness"}}},
		{"Object", MaterialParameters{"Light",	std::vector<std::string>{"Plank_BaseColor", "Plank_Roughness"}}}
	};

	std::unordered_map<std::string, ShaderParameters> shaderParameters = 
	{
		{"Default", ShaderParameters{"default.vert",	"default.frag"}},
		{"Light", ShaderParameters{"light.vert",	"light.frag"}}
	};

	std::unordered_map<std::string, MeshParameters> meshParameters = 
	{
		{"Sword", MeshParameters{"Sword.txt"}},
		{"Grass", MeshParameters{"Grass.txt"}},
		{"Object", MeshParameters{"Object.txt"}}
	};
	
	std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
	std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;

	std::shared_ptr<Shader> MakeShader(const std::string& shaderName, const ShaderParameters& parameters, bool replaceIfAlreadyExists)
	{
		if (loadedShaders.count(shaderName) && !replaceIfAlreadyExists) throw std::runtime_error("Tried To Make Same Shader Twice. Shader: " + shaderName);

		auto newShader = std::make_shared<Shader>(parameters.vertShader, parameters.fragShader);
		loadedShaders.emplace(shaderName, newShader);

		return newShader;
	}

	std::shared_ptr<Texture> GetTexture(const std::string& textureName)
	{
		auto texEntry = loadedTextures.find(textureName);
		if (texEntry != loadedTextures.end())	// The texture is already loaded.
		{
			return texEntry->second;
		}
		auto texParams = textureParameters.find(textureName);
		if (texParams == textureParameters.end())
			throw std::runtime_error("Tried To Access Imaginary Texture Parameters. Texture Name: " + textureName); // Some texture data was not found
		
		auto tex = std::make_shared<Texture>(texParams->second);
		loadedTextures.emplace(textureName, tex);
		return tex;
	}

	std::vector<std::shared_ptr<Texture>> GetTextures(const std::vector<std::string>& textureNames)
	{
		std::vector<std::shared_ptr<Texture>> textures;
		textures.reserve(textureNames.size());

		for (const auto& textureName : textureNames)
		{
			textures.push_back(GetTexture(textureName));
		}

		return textures;
	}

	std::shared_ptr<Material> GetMaterial(const std::string& materialName)
	{
		auto materialEntry = materialParameters.find(materialName);
		if (materialEntry == materialParameters.end())
			throw std::runtime_error("Tried To Access Imaginary Material Parameters. Material Name: " + materialName);

		return std::make_shared<Material>(GetShader(materialEntry->second.shaderName), GetTextures(materialEntry->second.textures));
	}

	std::shared_ptr<Mesh> GetMesh(const std::string& meshName)
	{
		auto meshEntry = loadedMeshes.find(meshName);
		if (meshEntry != loadedMeshes.end()) return meshEntry->second;	// The mesh was found and returned

		auto meshParams = meshParameters.find(meshName);
		if (meshParams == meshParameters.end()) 
			throw std::runtime_error("Tried To Access Imaginary Mesh Parameters. Mesh Name: " + meshName); // The mesh data was not found
		
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		ReadFromObjIntoVectors(meshParams->second.meshName, vertices, indices);
		
		auto mesh = std::make_shared<Mesh>(vertices, indices);
		loadedMeshes.emplace(meshName, mesh);
		
		return mesh;
	}

	std::shared_ptr<Shader> GetShader(const std::string& shaderName)
	{
		auto shaderEntry = loadedShaders.find(shaderName);
		if (shaderEntry == loadedShaders.end())
		{
			auto shaderParamsEntry = shaderParameters.find(shaderName);
			if(shaderParamsEntry == shaderParameters.end())
				throw std::runtime_error("Tries To Access Imaginary Shader. Shader Name: " + shaderName);
			return MakeShader(shaderName, shaderParamsEntry->second, false);
		}
		return shaderEntry->second;
	}
}