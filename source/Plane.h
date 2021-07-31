#pragma once
#include "Primitive.h"

class Plane final : public Primitive
{
public:
	Plane(const Elite::FPoint3& origin, const Elite::FVector3& direction, const Elite::RGBColor& color = Elite::RGBColor{ 1.f, 1.f, 1.f }, CullMode cullmode = CullMode::Backface);
	Plane(const Plane& p) = delete;
	Plane(Plane&& p) = delete;
	Plane& operator=(const Plane& p) = delete;
	Plane& operator=(Plane&& p) = delete;
	virtual ~Plane() = default;

	void Update(float deltaT) override {}
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck = false) const override;

private:
	Elite::FVector3 m_Direction;

};

