#pragma once
#include "Triangle.h"

using namespace Elite;
Triangle::Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, const Elite::RGBColor& color, CullMode cullmode)
    : Primitive(Elite::FPoint3(), color, cullmode)
    , m_Vertices(3)
    , m_Normal()
    , m_NormalLength()
{
    //Initialize vertices
    m_Vertices[0] = v0;
    m_Vertices[1] = v1;
    m_Vertices[2] = v2;

    //Precalculate normal at start
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);

    //Precalculate center (= origin)
    m_Origin.x = (v0.x + v1.x + v2.x) / 3.f;
    m_Origin.y = (v0.y + v1.y + v2.y) / 3.f;
    m_Origin.z = (v0.z + v1.z + v2.z) / 3.f;
}

Triangle::Triangle(const Elite::FPoint3& center, float size, const Elite::RGBColor& color, CullMode cullmode)
    : Primitive(center, color, cullmode) 
    , m_Vertices(3)
    , m_Normal()
    , m_NormalLength()
{
    //Initialize vertices
    m_Vertices[0] = FPoint3{ center.x - size, center.y + size, center.z };
    m_Vertices[1] = FPoint3{ center.x - size, center.y - size, center.z };
    m_Vertices[2] = FPoint3{ center.x + size, center.y - size, center.z };
                            
    //Precalculate normal at start
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);

    //Center = origin
    m_Origin = center;
}

void Triangle::Update(float deltaT)
{
    //Matrices
    FMatrix4 translationToOrigin = MakeTranslation(-FVector3(m_Origin));
    FMatrix3 rotationMatrix = MakeRotationY(deltaT);
    FMatrix4 translateBack = MakeTranslation(FVector3(m_Origin));

    for (int i = 0; i < 3; ++i)
    {
        //Translate to center 
        m_Vertices[i] = FPoint3(translationToOrigin * FPoint4(m_Vertices[i], 1.f));

        //Rotate
        m_Vertices[i] = FPoint3(rotationMatrix * FVector3(m_Vertices[i]));

        //Translate back
        m_Vertices[i] = FPoint3(translateBack * FPoint4(m_Vertices[i], 1.f));
    }

    //Recalculate normal
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowCheck) const
{
    //Front or backface check, if none is selected then it will simply continue
    float dot = Dot(m_Normal, ray.Direction);

    if (!isShadowCheck)
    {
        if (m_CullMode == CullMode::Backface && dot > 0)
            return false;
        if (m_CullMode == CullMode::Frontface && dot < 0)
            return false;
    }
    else
    {
        if (m_CullMode == CullMode::Backface && dot < 0)
            return false;
        if (m_CullMode == CullMode::Frontface && dot > 0)
            return false;
    }

    if (dot >= 0 - FLT_EPSILON && dot <= 0 + FLT_EPSILON)
        return false;

    //Continueing
    FVector3 L{ m_Origin - ray.Origin };
    float t = Dot(L, m_Normal) / Dot(ray.Direction, m_Normal);

    if (t < ray.tMin || t > ray.tMax)
        return false;

    //Intersection point on triangle
    FPoint3 intersectionPoint = ray.Origin + t * ray.Direction;
   
    //Check first edge
    FVector3 edgeA = m_Vertices[1] - m_Vertices[0];
    FVector3 toIntersection{ intersectionPoint - m_Vertices[0] };

    bool isInside = (Dot(Cross(toIntersection, edgeA), m_Normal) > 0);
    if (isInside)
    {
        //Check second edge
        FVector3 edgeB = m_Vertices[2] - m_Vertices[1];
        toIntersection = intersectionPoint - m_Vertices[1];

        isInside = (Dot(Cross(toIntersection, edgeB), m_Normal) > 0);
        if (isInside)
        {
            //Check third and last edge
            FVector3 edgeC = m_Vertices[0] - m_Vertices[2];
            toIntersection = intersectionPoint - m_Vertices[2];

            isInside = (Dot(Cross(toIntersection, edgeC), m_Normal) > 0);
            if (isInside)
            {
                //Ray is intersecting 
                if (!isShadowCheck)
                {
                    hitRecord.HitPos = intersectionPoint;
                    hitRecord.tValue = t;
                    hitRecord.Color = m_Color;
                    hitRecord.Normal = m_Normal;
                }
                return true;
            }
        }
    }
    return false;
}
