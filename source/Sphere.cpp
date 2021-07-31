#pragma once
#include "Sphere.h"

Sphere::Sphere(const Elite::FPoint3& origin, const Elite::RGBColor& color, float radius, CullMode cullmode)
	: Primitive(origin, color, cullmode)
	, m_Radius(radius)
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck) const
{
	//Analytic solution
	FVector3 sphereToRay{ ray.Origin - m_Origin };

	float A = Dot(ray.Direction, ray.Direction);
	float B = Dot(2 * ray.Direction, sphereToRay);
	float C = (Dot(sphereToRay, sphereToRay)) - (m_Radius * m_Radius);

	float discriminant = (B * B) - (4 * A * C);
	if (discriminant > 0)
	{
		float sqrdDiscriminant = sqrt(discriminant);
		float T = (-B - sqrdDiscriminant) / (2 * A);

		if (T < ray.tMin)
		{
			T = (-B + sqrdDiscriminant) / (2 * A);
		}

		if (T > ray.tMin && T < ray.tMax)
		{
			if (!isShadowCheck)
			{
				hitRecord.HitPos = ray.Origin + T * ray.Direction;
				hitRecord.Normal = (hitRecord.HitPos - m_Origin) / m_Radius;
				hitRecord.Color = m_Color;
				hitRecord.tValue = T;
			}

			return true;
		}
	}
	return false;
}
