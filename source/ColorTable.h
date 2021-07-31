#pragma once
#include "ERGBColor.h"
#include <map>

namespace COLOR
{
	enum class EColorName : int
	{
		White,
		Black,
		Silver,
		Melon,
		Silk,
		OldLace,
		CrystalBlue,
		PaleCerulean,
		ColumbiaBlue,
		SoftPurple,
		RoyalYellow
	};

	static std::map<const EColorName, Elite::RGBColor> ColorTable
	{
		{ EColorName::White, Elite::RGBColor(1.f, 1.f, 1.f) },
		{ EColorName::Black, Elite::RGBColor(0.f, 0.f, 0.f) },
		{ EColorName::Silver, Elite::RGBColor(192.f / 255.f, 192.f / 255.f, 192.f / 255.f) },
		{ EColorName::Melon, Elite::RGBColor(243.f / 255.f, 191.f / 255.f, 179.f / 255.f) },
		{ EColorName::Silk, Elite::RGBColor(255.f / 255.f, 221.f / 255.f, 211.f / 255.f) },
		{ EColorName::OldLace, Elite::RGBColor(253.f / 255.f, 248.f / 255.f, 226.f / 255.f) },
		{ EColorName::CrystalBlue, Elite::RGBColor(94.f / 255.f, 169.f / 255.f, 190.f / 255.f) },
		{ EColorName::PaleCerulean, Elite::RGBColor(154.f / 255.f, 205.f / 255.f, 224.f / 255.f) },
		{ EColorName::ColumbiaBlue, Elite::RGBColor(203.f / 255.f, 225.f / 255.f, 239.f / 255.f) },
		{ EColorName::SoftPurple, Elite::RGBColor(188.f / 255.f, 160.f / 255.f, 220.f / 255.f) },
		{ EColorName::RoyalYellow, Elite::RGBColor(250.f / 255.f, 218.f / 255.f, 94.f / 255.f) }
	};
}

