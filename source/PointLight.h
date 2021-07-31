#pragma once
#include "Light.h"

class PointLight final : public Light
{
public:
	PointLight(const Elite::FPoint3& pos, const Elite::RGBColor& color, float intensity);

	Elite::RGBColor GetCalculatedIrradianceColor(const HitRecord& hitRecord) override;
	void CalculateShadowRay(const HitRecord& hitRecord, Ray& outputRay) override;
	Elite::FVector3 GetDirection(const HitRecord& hitRecord) override;

private:
	Elite::FPoint3 m_Position;
};

