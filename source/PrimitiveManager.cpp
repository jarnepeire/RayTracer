#pragma once
#include "PrimitiveManager.h"
#include "Primitive.h"

PrimitiveManager::PrimitiveManager()
{
}

PrimitiveManager::~PrimitiveManager()
{
	for (size_t t = 0; t < m_pPrimitives.size(); t++)
	{
		delete m_pPrimitives[t];
		m_pPrimitives[t] = nullptr;
	}

	m_pPrimitives.clear();
}

void PrimitiveManager::AddPrimitive(Primitive* primitive)
{
	if (primitive)
		m_pPrimitives.push_back(primitive);
}
