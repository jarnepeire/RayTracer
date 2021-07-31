#pragma once
#include "Material.h"

class Material_Lambert final : public Material
{
public:
	Material_Lambert(const Elite::RGBColor& color, float reflectance);
	virtual ~Material_Lambert() = default;

	Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const override;
	const Elite::RGBColor& GetDiffuseColor() const override;

private:
	Elite::RGBColor m_Color;
	float m_Reflectance;
};

