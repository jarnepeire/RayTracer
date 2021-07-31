#pragma once
#include "LightManager.h"
#include "Light.h"

LightManager::~LightManager()
{
	for (size_t t = 0; t < m_pLights.size(); t++)
	{
		delete m_pLights[t];
		m_pLights[t] = nullptr;
	}

	m_pLights.clear();
}

size_t LightManager::AddLight(Light* pLight)
{
	if (pLight)
	{
		size_t index = m_pLights.size();
		m_pLights.push_back(pLight);
		return index;
	}
	return size_t(-1);
}
