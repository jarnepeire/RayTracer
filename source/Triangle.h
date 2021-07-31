#pragma once
#include "Primitive.h"
#include <vector>

class Triangle final : public Primitive
{
public:
	/* Define the 3 vertices manually to make a triangle */
	Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, const Elite::RGBColor& color, CullMode cullmode = CullMode::Backface);

	/* Define a center point with a size to make a triangle 
		size = half of total desired width */
	Triangle(const Elite::FPoint3& center, float size, const Elite::RGBColor& color, CullMode cullmode = CullMode::Backface);

	Triangle(const Triangle& p) = default;
	Triangle(Triangle&& p) noexcept = default;
	Triangle& operator=(const Triangle& p) = default;
	Triangle& operator=(Triangle&& p) = default;
	virtual ~Triangle() = default;

	void Update(float deltaT) override;
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck = false) const override;

private:
	std::vector<Elite::FPoint3> m_Vertices;
	Elite::FVector3 m_Normal;
	float m_NormalLength;
};

