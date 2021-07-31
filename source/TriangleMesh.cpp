#pragma once
#include "TriangleMesh.h"
#include "ObjParser.h"

TriangleMesh::TriangleMesh(const char* filepath)
	: Primitive(Elite::FPoint3(), {})
{
	//Parse file and turn into triangles to store here
	std::vector<int> indexBuffer;
	std::vector<Elite::FPoint3> vertexBuffer;

	ObjParser parser{ filepath };
	parser.LoadBuffers(indexBuffer, vertexBuffer);

	//Now we can start creating our list of triangles
	for (size_t i = 0; i < indexBuffer.size(); i += 3)
	{
		//Push triangle in list
		m_Triangles.push_back(Triangle
			{ 
				vertexBuffer[indexBuffer[i]], 
				vertexBuffer[indexBuffer[(i + 1)]], 
				vertexBuffer[indexBuffer[(i + 2)]], 
				{},
				CullMode::Backface 
			}
		);
	}
}

TriangleMesh::~TriangleMesh()
{
	m_Triangles.clear();
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck) const
{
	//Loop over all triangles and render the first one to be hit
	for (const Triangle& triangle : m_Triangles)
	{
		bool isHit = triangle.Hit(ray, hitRecord, isShadowCheck);
		if (isHit)
			return true;
	}
	return false;
}
