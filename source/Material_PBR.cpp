#pragma once
#include "Material_PBR.h"
#include "BRDF.h"
#include "Structs.h"

Material_PBR::Material_PBR(const Elite::RGBColor& albedoColor, bool isMetal, float roughness)
	: m_AlbedoColor(albedoColor)
	, m_Metalness( (isMetal) ? 1 : 0)
	, m_Roughness(roughness)
{
}

Elite::RGBColor Material_PBR::Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const
{
	return BRDF::LambertCookTorrance(m_AlbedoColor, m_Metalness, m_Roughness, l, v, hitRecord.Normal);
}

const Elite::RGBColor& Material_PBR::GetDiffuseColor() const
{
	return m_AlbedoColor;
}
