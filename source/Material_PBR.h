#pragma once
#include "Material.h"

class Material_PBR final : public Material
{
public:
	Material_PBR(const Elite::RGBColor& albedoColor, bool isMetal, float roughness);
	virtual ~Material_PBR() = default;

	Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const override;
	const Elite::RGBColor& GetDiffuseColor() const override;

private:
	Elite::RGBColor m_AlbedoColor;
	int m_Metalness;
	float m_Roughness;

};

