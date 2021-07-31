#pragma once
#include "EMath.h"
#include "ERGBColor.h"
using namespace Elite;

struct Ray
{
	FPoint3 Origin = {};
	FVector3 Direction = {};
	float tMin = 0.0001f;
	float tMax = FLT_MAX;
};

struct HitRecord
{
	FPoint3 HitPos = {};
	FVector3 Normal = {};
	RGBColor Color = {};
	float tValue = {};
	float tClosest = FLT_MAX;
};

/* Don't forget to update the _NR_OF_OPTIONS when adding new options */
enum class ImageRenderInfo : unsigned int
{
	All = 0,
	OnlyIrradiance = 1,
	OnlyBRDF = 2,
	_NR_OF_OPTIONS = 3
};

struct KeyBindInfo
{
	bool UseDirectionalLight = true;
	bool UseLeftPointLight = true;
	bool UseRightPointLight = true;
	bool UseHardShadows = true;
	
	ImageRenderInfo ImageRenderInfo = ImageRenderInfo::All;
};