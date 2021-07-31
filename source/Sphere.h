#pragma once
#include "Primitive.h"

class Sphere final : public Primitive
{
public:
	Sphere(const Elite::FPoint3& origin, const Elite::RGBColor& color, float radius, CullMode cullmode = CullMode::Backface);
	Sphere(const Sphere& p) = delete;
	Sphere(Sphere&& p) = delete;
	Sphere& operator=(const Sphere& p) = delete;
	Sphere& operator=(Sphere&& p) = delete;
	virtual ~Sphere() = default;

	void Update(float deltaT) override {}
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck = false) const override;

private:
	float m_Radius;
};

