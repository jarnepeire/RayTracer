#pragma once
#include "Triangle.h"
#include <vector>

class TriangleMesh final : public Primitive
{
public:
	TriangleMesh(const char* filepath);
	TriangleMesh(const TriangleMesh& p) = delete;
	TriangleMesh(TriangleMesh&& p) = delete;
	TriangleMesh& operator=(const TriangleMesh& p) = delete;
	TriangleMesh& operator=(TriangleMesh&& p) = delete;
	virtual ~TriangleMesh();

	void Update(float deltaT) override {}
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck = false) const override;

private:
	std::vector<Triangle> m_Triangles;
};

