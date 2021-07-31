#pragma once
#include "Material_Lambert.h"
#include "BRDF.h"

Material_Lambert::Material_Lambert(const Elite::RGBColor& color, float reflectance)
	: m_Color(color)
	, m_Reflectance(reflectance)
{
}

Elite::RGBColor Material_Lambert::Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const
{
	return BRDF::Lambert(m_Color, m_Reflectance);
}

const Elite::RGBColor& Material_Lambert::GetDiffuseColor() const
{
	return m_Color;
}
