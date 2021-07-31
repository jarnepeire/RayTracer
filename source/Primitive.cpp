#pragma once
#include "Primitive.h"

Primitive::Primitive(const Elite::FPoint3& origin, const Elite::RGBColor& color, CullMode cullmode)
	: m_Origin(origin)
	, m_Color(color)
	, m_CullMode(cullmode)
{
}
