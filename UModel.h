#pragma once
#include "UMaterial.h"
#include "UStaticMesh.h"

class UModel
{
public:

	std::shared_ptr<UMaterial> material;
	std::shared_ptr<UStaticMesh> mesh;

	UModel(const std::string& meshName, const std::string& materialName);

	void ActivateModel(UCamera& camera);

	void SetupModel(const std::string& meshName, const std::string& materialName);

	void SetMesh(const std::string& meshName);
	void SetMaterial(const std::string& materialName);

	template<typename Func, typename ...Args>
	inline void CallGLUniform(Func func, const char* name, Args && ...args)
	{
		func(glGetUniformLocation(material->shader->ID, name), std::forward<Args>(args)...);
	}
};

