#pragma once
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& color, float intensity)
	: Light(color, intensity)
	, m_Direction(direction)
{
}

Elite::RGBColor DirectionalLight::GetCalculatedIrradianceColor(const HitRecord& hitRecord)
{
	float lambertCosineLaw = Dot(hitRecord.Normal, Elite::GetNormalized(m_Direction));
	if (lambertCosineLaw < 0)
		return Elite::RGBColor();

	Elite::RGBColor Ergb = m_Color * m_LightIntensity;
	return Ergb * lambertCosineLaw;
}

void DirectionalLight::CalculateShadowRay(const HitRecord& hitRecord, Ray& outputRay)
{
	//Hard shadow check
	FVector3 shadowRayDirection = m_Direction;
	float tMax = Normalize(shadowRayDirection);

	//Fill in ray info
	outputRay.Origin = hitRecord.HitPos + (0.001f * hitRecord.Normal);
	outputRay.Direction = shadowRayDirection;
	outputRay.tMax = tMax;
}

Elite::FVector3 DirectionalLight::GetDirection(const HitRecord& hitRecord)
{
	return m_Direction;
}
