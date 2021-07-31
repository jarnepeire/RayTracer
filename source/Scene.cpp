#pragma once
//SDL + Scene
#include "SDL.h"
#include "Scene.h"

//Primitives
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"

//Lights
#include "PointLight.h"
#include "DirectionalLight.h"

//Materials
#include "Material_Lambert.h"
#include "Material_LambertPhong.h"
#include "Material_PBR.h"

//Other
#include "ERenderer.h"
#include "Camera.h"

Scene::Scene(SDL_Window* pWindow, const std::string& sceneTag)
	: m_SceneIndex(-1)
	, m_SceneTag(sceneTag)
	, m_Height()
	, m_Width()
	, m_KeyBindInfo()
	, m_FirstSpaces()
	, m_LastSpaces()
	, m_pRenderer(new Elite::Renderer(pWindow))
	, m_pCamera(new Camera())
	, m_Input()
	, m_PrimitiveManager()
	, m_LightManager()
	, m_MaterialManager()
	, m_TotalWhiteSpaces(44) //Width of info box in console
{
	SDL_GetWindowSize(pWindow, &m_Width, &m_Height);
}

Scene::~Scene()
{
	delete m_pRenderer;
	delete m_pCamera;
}

void Scene::AddPrimitive(Primitive* primitive)
{
	m_PrimitiveManager.AddPrimitive(primitive);
}

size_t Scene::AddLight(Light* pLight)
{
	return m_LightManager.AddLight(pLight);
}

void Scene::AddMaterial(Material* pMaterial)
{
	m_MaterialManager.AddMaterial(pMaterial);
}

void Scene::RootInitialize()
{
	//Init variables by default
	m_pCamera->Initialize(Elite::FPoint3(0.f, 3.f, 12.5f), float(m_Width), float(m_Height), 45.f);
	InitializeSpacingForKeybindInfo();
}

void Scene::RootUpdate(float deltaT)
{
	m_Input.ProcessInput();
	m_pCamera->Update(m_Input, deltaT);
	
	//Update primitives
	const auto& primitives = m_PrimitiveManager.GetPrimitives();
	for (Primitive* prim : primitives)
	{
		prim->Update(deltaT);
	}
}

void Scene::RootRender()
{
	//Multithreaded render
	m_pRenderer->Render(this);
}

void Scene::InitializeSpacingForKeybindInfo()
{
	unsigned int nameSize = (unsigned int)m_SceneTag.size();
	unsigned int leftOverSpaceSize = m_TotalWhiteSpaces - nameSize;
	bool isOddLeftOverSpace = (leftOverSpaceSize % 2 != 0);
	leftOverSpaceSize /= 2;

	m_FirstSpaces.insert(0, (leftOverSpaceSize + static_cast<unsigned int>(isOddLeftOverSpace)), ' ');
	m_FirstSpaces.push_back('|');
	std::reverse(m_FirstSpaces.begin(), m_FirstSpaces.end());

	m_LastSpaces.insert(0, leftOverSpaceSize, ' ');
	m_LastSpaces.push_back('|');
}

void Scene::SetSceneIndex(int sceneIdx)
{
	m_SceneIndex = sceneIdx;
}
