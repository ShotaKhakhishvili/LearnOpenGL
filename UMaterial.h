#pragma once
#include "Shader.h"
#include "UTexture.h"
#include "UCamera.h"
#include <vector>
#include <unordered_map>

struct MaterialParameters
{
	const std::string shaderName;
	std::vector<std::string> textures;
};

class UMaterial {
public:
    std::shared_ptr<Shader> shader; 
	std::vector<std::shared_ptr<UTexture>> textures;

	UMaterial(const std::shared_ptr<Shader>& shaderIn, const std::vector<std::shared_ptr<UTexture>>& texturesIn)
		: shader(shaderIn), textures(texturesIn)
	{

	}
};