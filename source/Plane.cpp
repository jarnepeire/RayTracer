#pragma once
#include "Plane.h"

Plane::Plane(const Elite::FPoint3& origin, const Elite::FVector3& direction, const Elite::RGBColor& color, CullMode cullmode)
	: Primitive(origin, color, cullmode)
	, m_Direction(Elite::GetNormalized(direction))
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck) const
{
	float dot = Dot(ray.Direction, m_Direction);
	if (!isShadowCheck)
	{
		if (m_CullMode == CullMode::Backface && dot > 0)
			return false;
		else if (m_CullMode == CullMode::Frontface && dot < 0)
			return false;
	}
	else
	{
		if (m_CullMode == CullMode::Backface && dot < 0)
			return false;
		else if (m_CullMode == CullMode::Frontface && dot > 0)
			return false;
	}

	float T = Dot((m_Origin - ray.Origin), m_Direction) / dot;
	if (T > ray.tMin && T < ray.tMax)
	{
		if (!isShadowCheck)
		{
			hitRecord.HitPos = ray.Origin + T * ray.Direction;
			hitRecord.Normal = m_Direction;
			hitRecord.Color = m_Color;
			hitRecord.tValue = T;
		}

		return true;
	}
	else
	{
		return false;
	}
}
