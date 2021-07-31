#pragma once
#include "Material.h"

class Material_LambertPhong final : public Material
{
public:
	Material_LambertPhong(const Elite::RGBColor& diffColor, float diffReflecance, float specReflectance, float phongExp);
	virtual ~Material_LambertPhong() = default;

	Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const override;
	const Elite::RGBColor& GetDiffuseColor() const override;

private:
	Elite::RGBColor m_DiffuseColor;
	float m_DiffuseReflectance;
	float m_SpecularReflectance;
	float m_PhongExponent;
};

