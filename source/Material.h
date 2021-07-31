#pragma once
#include "EMath.h"
#include "ERGBColor.h"

struct HitRecord;
class Material
{
public:
	Material() = default;
	Material(const Material& m) = delete;
	Material(Material&& m) = delete;
	Material& operator=(const Material& m) = delete;
	Material& operator=(Material&& m) = delete;
	virtual ~Material() = default;

	/* Calculate and return shaded color for passed hit position
		l = light direction so from lightPos -> hitPos 
		v = view direction inversed so from hitPos -> eyePos */
	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& l, const Elite::FVector3& v) const = 0;
	
	/* Return the diffuse color of the material */
	virtual const Elite::RGBColor& GetDiffuseColor() const = 0;
};

