#pragma once
#include <vector>

class Primitive;
class PrimitiveManager final
{
public:
	PrimitiveManager();
	PrimitiveManager(const PrimitiveManager& pm) = delete;
	PrimitiveManager(PrimitiveManager&& pm) noexcept = delete;
	PrimitiveManager& operator=(const PrimitiveManager& pm) = delete;
	PrimitiveManager& operator=(PrimitiveManager&& pm) noexcept = delete;
	~PrimitiveManager();

	/* Adds a primitive to the list if primitive is non-nullptr*/
	void AddPrimitive(Primitive* primitive);

	/* Return reference to the vector of all primitives */
	const std::vector<Primitive*>& GetPrimitives() const { return m_pPrimitives; }

private:
	std::vector<Primitive*> m_pPrimitives;
};

