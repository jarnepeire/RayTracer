#pragma once
#include "Light.h"

Light::Light(const Elite::RGBColor& color, float intensity)
	: m_Color(color)
	, m_LightIntensity(intensity)
	, m_IsActive(true)
{
}
