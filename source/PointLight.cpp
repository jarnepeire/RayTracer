#pragma once
#include "PointLight.h"

PointLight::PointLight(const Elite::FPoint3& pos, const Elite::RGBColor& color, float intensity)
    : Light(color, intensity)
    , m_Position(pos)
{
}

Elite::RGBColor PointLight::GetCalculatedIrradianceColor(const HitRecord& hitRecord)
{
    Elite::FVector3 dir{ m_Position - hitRecord.HitPos };
    float lambertCosineLaw = Dot(hitRecord.Normal, Elite::GetNormalized(dir));
    if (lambertCosineLaw < 0)
        return Elite::RGBColor();

    Elite::RGBColor Ergb = m_Color * m_LightIntensity / Elite::SqrMagnitude(dir);
    return (Ergb * lambertCosineLaw);
}

void PointLight::CalculateShadowRay(const HitRecord& hitRecord, Ray& outputRay)
{
    //Hard shadow check
    FVector3 shadowRayDirection = m_Position - hitRecord.HitPos;
    float tMax = Normalize(shadowRayDirection);

    outputRay.Origin = hitRecord.HitPos + (0.001f * hitRecord.Normal);
    outputRay.Direction = shadowRayDirection;
    outputRay.tMax = tMax;
}

Elite::FVector3 PointLight::GetDirection(const HitRecord& hitRecord)
{
    return Elite::GetNormalized(Elite::FVector3(m_Position - hitRecord.HitPos));
}
