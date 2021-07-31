#pragma once
#include <vector>

class Material;
class MaterialManager final
{
public:
	MaterialManager() = default;
	MaterialManager(const MaterialManager& m) = delete;
	MaterialManager(MaterialManager&& m) = delete;
	MaterialManager& operator=(const MaterialManager& m) = delete;
	MaterialManager& operator=(MaterialManager&& m) = delete;
	~MaterialManager();

	/* Add a new material to the manager */
	void AddMaterial(Material* pMaterial);

	/* Return reference to vector of all materials */
	const std::vector<Material*>& GetMaterials() const { return m_pMaterials; }

private:
	std::vector<Material*> m_pMaterials;
};

