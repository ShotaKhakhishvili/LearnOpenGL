#pragma once
#include "Material.h"
#include "Mesh.h"

class Model
{
public:

	std::shared_ptr<Material> material;
	std::shared_ptr<Mesh> mesh;

	Model(const std::string& meshName, const std::string& materialName);

	void ActivateModel(Camera& camera);

	void SetupModel(const std::string& meshName, const std::string& materialName);

	void SetMesh(const std::string& meshName);
	void SetMaterial(const std::string& materialName);

	template<typename Func, typename ...Args>
	inline void CallGLUniform(Func func, const char* name, Args && ...args)
	{
		func(glGetUniformLocation(material->shader->ID, name), std::forward<Args>(args)...);
	}
};

