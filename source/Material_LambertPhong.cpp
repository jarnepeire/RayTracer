#pragma once
#include "Material_LambertPhong.h"
#include "BRDF.h"
#include "Structs.h"

Material_LambertPhong::Material_LambertPhong(const Elite::RGBColor& diffColor, float diffReflecance, float specReflectance, float phongExp)
	: m_DiffuseColor(diffColor)
	, m_DiffuseReflectance(diffReflecance)
	, m_SpecularReflectance(specReflectance)
	, m_PhongExponent(phongExp)
{
}

Elite::RGBColor Material_LambertPhong::Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const
{
	return BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance) + BRDF::Phong(m_SpecularReflectance, m_PhongExponent, l, v, hitRecord.Normal);
}

const Elite::RGBColor& Material_LambertPhong::GetDiffuseColor() const
{
	return m_DiffuseColor;
}
