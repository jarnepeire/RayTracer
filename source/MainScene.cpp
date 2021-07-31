#pragma once
//Scene
#include "MainScene.h"

//Materials
#include "Material_Lambert.h"
#include "Material_LambertPhong.h"
#include "Material_PBR.h"

//Lights
#include "PointLight.h"
#include "DirectionalLight.h"

//Primitives
#include "Plane.h"
#include "Triangle.h"
#include "Sphere.h"

//Other
#include "Camera.h"
#include "ColorTable.h"
#include <iostream>

using namespace Elite;
MainScene::MainScene(SDL_Window* pWindow, const std::string& sceneTag)
	: Scene(pWindow, sceneTag)
	, m_IndexLeftPointLight()
	, m_IndexRightPointLight()
	, m_IndexDirectionalLight()
{
}

void MainScene::Initialize()
{
	auto pCamera = GetCamera();
	pCamera->SetPosition(0.f, 4.f, 12.f);
	pCamera->SetTranslationSpeed(1.5f);
	pCamera->SetRotationSpeed(0.25f);

	AddPrimitives();
	AddLights();
	AddMaterials();
}

void MainScene::Update(float deltaT)
{
	UpdateKeyBindInfo();
}

void MainScene::Render()
{
}

void MainScene::AddPrimitives()
{
	//Planes
	AddPrimitive(new Plane(FPoint3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.f), {}));
	AddPrimitive(new Plane(FPoint3(0.f, 0.f, -10.f), FVector3(0.f, 0.f, 1.f), {}));
	AddPrimitive(new Plane(FPoint3(5.5f, 0.f, 0.f), FVector3(-1.f, 0.f, 0.f), {}));
	AddPrimitive(new Plane(FPoint3(-5.5f, 0.f, 0.f), FVector3(1.f, 0.f, 0.f), {}));
	AddPrimitive(new Plane(FPoint3(0.f, 11.f, 0.f), FVector3(0.f, -1.f, 0.f), {}));

	//Spheres
	AddPrimitive(new Sphere(FPoint3(-2.5f, 1.25f, 0.f), {}, 1.f)); 
	AddPrimitive(new Sphere(FPoint3(0.f, 1.25f, 0.f), {}, 1.f)); 
	AddPrimitive(new Sphere(FPoint3(2.5f, 1.25f, 0.f), {}, 1.f));

	AddPrimitive(new Sphere(FPoint3(-2.5f, 3.75f, 0.f), {}, 1.f));
	AddPrimitive(new Sphere(FPoint3(0.f, 3.75f, 0.f), {}, 1.f));
	AddPrimitive(new Sphere(FPoint3(2.5f, 3.75f, 0.f), {}, 1.f));

	//Triangles
	AddPrimitive(new Triangle(FPoint3(-2.5f, 6.75f, 0.f), 1.f, {}, Primitive::CullMode::Frontface));
	AddPrimitive(new Triangle(FPoint3(0.f, 6.75f, 0.f), 1.f, {}, Primitive::CullMode::Backface));
	AddPrimitive(new Triangle(FPoint3(2.5f, 6.75f, 0.f), 1.f, {}, Primitive::CullMode::None));
}

void MainScene::AddLights()
{
	m_IndexLeftPointLight = AddLight(new PointLight(FPoint3(0, 5.f, -5.f), COLOR::ColorTable[COLOR::EColorName::ColumbiaBlue], 30.f));
	m_IndexRightPointLight = AddLight(new PointLight(FPoint3(0, 5.f, 5.f), COLOR::ColorTable[COLOR::EColorName::Melon], 30.f));
	m_IndexDirectionalLight = AddLight(new DirectionalLight(FVector3(0.f, 0.77f, 0.77f), COLOR::ColorTable[COLOR::EColorName::White], 0.6f));
}

void MainScene::AddMaterials()
{
	//Planes
	AddMaterial(new Material_Lambert(COLOR::ColorTable[COLOR::EColorName::ColumbiaBlue], 1.f));
	AddMaterial(new Material_Lambert(COLOR::ColorTable[COLOR::EColorName::ColumbiaBlue], 1.f));
	AddMaterial(new Material_Lambert(COLOR::ColorTable[COLOR::EColorName::SoftPurple], 1.f));
	AddMaterial(new Material_Lambert(COLOR::ColorTable[COLOR::EColorName::RoyalYellow], 1.f));
	AddMaterial(new Material_Lambert(COLOR::ColorTable[COLOR::EColorName::ColumbiaBlue], 1.f));

	//Spheres
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], true, 1.f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], true, 0.6f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], true, 0.1f));
								 
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 1.f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 0.6f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 0.1f));
								 
	//Triangles					 
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 0.6f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 0.6f));
	AddMaterial(new Material_PBR(COLOR::ColorTable[COLOR::EColorName::Silver], false, 0.6f));
}

void MainScene::UpdateKeyBindInfo()
{
	const auto& input = GetInput();
	const auto& lightManager = GetLightManager();

	if (input.IsPressed(EKeyboardInput::DisplayKeyBindInfo))
		DisplayKeyBindInfo();

	else if (input.IsPressed(EKeyboardInput::LeftPointLight))
	{
		const auto& pLight = lightManager.GetLights()[m_IndexLeftPointLight];
		if (pLight) pLight->SetActive(!pLight->GetIsActive());
	}

	else if (input.IsPressed(EKeyboardInput::RightPointLight))
	{
		const auto& pLight = lightManager.GetLights()[m_IndexRightPointLight];
		if (pLight) pLight->SetActive(!pLight->GetIsActive());
	}

	else if (input.IsPressed(EKeyboardInput::DirectionalLight))
	{
		const auto& pLight = lightManager.GetLights()[m_IndexDirectionalLight];
		if (pLight) pLight->SetActive(!pLight->GetIsActive());
	}

	else if (input.IsPressed(EKeyboardInput::HardShadows))
		m_KeyBindInfo.UseHardShadows = !m_KeyBindInfo.UseHardShadows;

	else if (input.IsPressed(EKeyboardInput::ToggleRendering))
		m_KeyBindInfo.ImageRenderInfo = static_cast<ImageRenderInfo>(((int)m_KeyBindInfo.ImageRenderInfo + 1) % (int)ImageRenderInfo::_NR_OF_OPTIONS);
}


void MainScene::DisplayKeyBindInfo() const
{
	std::cout <<
		"+--------------------------------------------+\n" <<
		"|      Ray Tracer - Jarne Peire(2DAE02)      |\n" <<
		"+--------------------------------------------+\n" <<
		m_FirstSpaces << m_SceneTag << m_LastSpaces << "\n" <<
		"|                 Key Binds :                |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Display KeyBind Information          |  I  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Take Screenshot                      |  X  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Enable / Disable Directional Light   |  J  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Enable / Disable Left Point Light    |  K  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Enable / Disable Right Point Light   |  L  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Enable / Disable Hard Shadows        |  Z  |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Toggle between image rendering       |  T  |\n" <<
		"|  (BRDF, Irradiance, All)             |     |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Previous Scene                       |  F1 |\n" <<
		"+--------------------------------------+-----+\n" <<
		"| Next Scene                           |  F2 |\n" <<
		"+--------------------------------------+-----+\n";
}