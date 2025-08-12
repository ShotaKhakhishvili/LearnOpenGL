#pragma once
#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <unordered_map>

struct MaterialParameters
{
	const std::string shaderName;
	std::vector<std::string> textures;
};

class Material {
public:
    std::shared_ptr<Shader> shader; 
	std::vector<std::shared_ptr<Texture>> textures;

	Material(const std::shared_ptr<Shader>& shaderIn, const std::vector<std::shared_ptr<Texture>>& texturesIn)
		: shader(shaderIn), textures(texturesIn)
	{

	}
};