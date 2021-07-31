#pragma once
#include "Light.h"

class DirectionalLight final : public Light
{
public:
	DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& color, float intensity);

	Elite::RGBColor GetCalculatedIrradianceColor(const HitRecord& hitRecord) override;
	void CalculateShadowRay(const HitRecord& hitRecord, Ray& outputRay) override;;
	Elite::FVector3 GetDirection(const HitRecord& hitRecord) override;

private:
	Elite::FVector3 m_Direction;
};

