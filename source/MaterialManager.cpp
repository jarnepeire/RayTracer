#pragma once
#include "MaterialManager.h"
#include "Material.h"

MaterialManager::~MaterialManager()
{
	for (size_t t = 0; t < m_pMaterials.size(); ++t)
	{
		delete m_pMaterials[t];
		m_pMaterials[t] = nullptr;
	}
	m_pMaterials.clear();
}

void MaterialManager::AddMaterial(Material* pMaterial)
{
	if (pMaterial)
		m_pMaterials.push_back(pMaterial);
}
