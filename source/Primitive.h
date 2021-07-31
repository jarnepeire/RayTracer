#pragma once
#include "Structs.h"

class Primitive
{
public:
	enum class CullMode : unsigned int
	{
		Frontface = 0,
		Backface = 1,
		None = 2
	};
	virtual ~Primitive() = default;

	/* Update primitive */
	virtual void Update(float deltaT) = 0;

	/* Check if the given ray hits the primitive 
		Will overwrite hit record information on hit (except for shadow ray checks) */
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck = false) const = 0;

protected:
	Primitive(const Elite::FPoint3& origin, const Elite::RGBColor& color, CullMode cullmode = CullMode::Backface);

	Elite::FPoint3 m_Origin;
	Elite::RGBColor m_Color;
	CullMode m_CullMode;
};

