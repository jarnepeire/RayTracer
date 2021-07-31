#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "Structs.h"

class Light
{
public: 
	Light(const Elite::RGBColor& color, float intensity);
	Light(const Light& l) = delete;
	Light(Light&& l) = delete;
	Light& operator=(const Light& l) = delete;
	Light& operator=(Light&& l) = delete;
	~Light() = default;

	/* Calculate and return the irradiance at a certain point (hitPos from HitRecord) */
	virtual Elite::RGBColor GetCalculatedIrradianceColor(const HitRecord& hitRecord) = 0;

	/* Calculate and return the shadow ray at a certain point (hitPos from HitRecord) */
	virtual void CalculateShadowRay(const HitRecord& hitRecord, Ray& outputRay) = 0;

	/* Return normalized direction of light (differs for type of light) */
	virtual Elite::FVector3 GetDirection(const HitRecord& hitRecord) = 0;
	
	/* Return light color */
	const Elite::RGBColor& GetColor() const { return m_Color; }

	/* Return light intensity */
	float GetIntensity() const { return m_LightIntensity; }

	/* Check if a light is active in the scene */
	bool GetIsActive() const { return m_IsActive; }

	/* Set a light active or inactive in the scene */
	void SetActive(bool isActive) { m_IsActive = isActive; }

protected:
	Elite::RGBColor m_Color;
	float m_LightIntensity;
	bool m_IsActive;
};

