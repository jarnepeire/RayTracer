#pragma once
//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"
#include "Scene.h"
#include "Structs.h"
#include "Primitive.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

//Other 
#include <future>

Elite::Renderer::Renderer(SDL_Window * pWindow)
	: m_pWindow(pWindow)
	, m_pFrontBuffer(nullptr)
	, m_pBackBuffer(nullptr)
	, m_pBackBufferPixels(nullptr)
	, m_Width(0)
	, m_Height(0)
{
	//Initialize
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render(Scene* pScene)
{
	//LockSurface
	SDL_LockSurface(m_pBackBuffer);

	//Multithreading (source for help: https://medium.com/@phostershop/solving-multithreaded-raytracing-issues-with-c-11-7f018ecd76fa) 
	unsigned int max = m_Width * m_Height;
	unsigned int cores = std::thread::hardware_concurrency();
	std::vector<std::future<void>> futureVector;

	//Loop over all the cores
	for (unsigned int i = 0; i < cores; ++i)
	{
		futureVector.emplace_back(
			std::async([this, i, max, cores, &pScene]()
				{
					//Scene variables
					auto pCamera = pScene->GetCamera();
					const auto& pPrimitives = pScene->GetPrimitiveManager().GetPrimitives();
					const auto& pLights = pScene->GetLightManager().GetLights();
					const auto& pMaterials = pScene->GetMaterialManager().GetMaterials();
					const auto& keyBindInfo = pScene->GetKeyBindInfo();

					//Multithread with fixed indexing -> divide screen into segments (so that the screen is evenly divided over all cores)
					unsigned int segment = (unsigned int)std::floorf(max / float(cores));

					//Giving each thread a portion of where to start rendering from and where to stop (= what segment it needs to render)
					unsigned int startIdxCurrentThread = i * segment;
					unsigned int maxIdxCurrentThread = startIdxCurrentThread + segment;

					//Start pixel loop
					Ray cameraRay{};
					for (unsigned int index = startIdxCurrentThread; index < maxIdxCurrentThread && index < max; ++index)
					{
						//Create camera ray
						unsigned int x = index % m_Width;
						unsigned int y = index / m_Width;
						pCamera->CalculateCameraRay(x, y, cameraRay);

						//T is set to max, needs a check later who has the closest T value (closest to screen)
						HitRecord hitRecord{};
						RGBColor finalColor{ 0,0,0 };

						//Loop over all primitives to render
						for (size_t i = 0; i < pPrimitives.size(); ++i)
						{
							if (pPrimitives[i]->Hit(cameraRay, hitRecord))
							{
								//Check for who is more in front than the other primitive
								if (hitRecord.tValue < hitRecord.tClosest)
								{
									//Update closest hit
									hitRecord.tClosest = hitRecord.tValue;
									
									//Shade or re-shade for closest primitive with current material
									finalColor = ShadeCurrentPixel(pPrimitives, pLights, pMaterials[i], cameraRay, hitRecord, keyBindInfo);
								}
							}
						}

						//Clamp in case of overflow
						if (finalColor.r > 1.f || finalColor.g > 1.f || finalColor.b > 1.f)
							finalColor.MaxToOne();

						//Render current pixel with correct color
						m_pBackBufferPixels[x + (y * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
							static_cast<uint8_t>(finalColor.r * 255),
							static_cast<uint8_t>(finalColor.g * 255),
							static_cast<uint8_t>(finalColor.b * 255));
					}
				}));	
	}

	//Before updating our screen with the final image, we make sure all threads are done calculating the pixel colors
	for (auto& future : futureVector)
		future.wait();

	//Back to front buffer and update window with new image
	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

Elite::RGBColor Elite::Renderer::ShadeCurrentPixel(const std::vector<Primitive*>& pPrimitives, const std::vector<Light*>& pLights, Material* pMaterial, const Ray& cameraRay, HitRecord& hitRecord, const KeyBindInfo& keyBindInfo)
{
	//Reset new variables for calculating final color
	Elite::RGBColor irradiance{ 0,0,0 };
	Elite::RGBColor BRDF{ 0,0,0 };
	Elite::RGBColor finalColor{ 0,0,0 };

	Ray shadowRay{};
	for (Light* pLight : pLights)
	{
		//Check if we enabled this light or not
		if (!pLight->GetIsActive()) continue;

		//Option to enable/disable hard shadows
		if (keyBindInfo.UseHardShadows)
		{
			//Uses previous hit record information to calculate and store ray information in the shadowRay object 
			pLight->CalculateShadowRay(hitRecord, shadowRay);

			//Hard shadow check
			bool hitsPrimitive{};
			for (Primitive* pPrimitive : pPrimitives)
			{
				if (pPrimitive->Hit(shadowRay, hitRecord, true))
				{
					hitsPrimitive = true;
					break;
				}
			}

			//If primitive is hit, it means something is blocking the path of the ray 
			// -> we skip light calculation because there's no light contribution at this point
			if (hitsPrimitive) continue;
		}

		//Otherwise continue calculations (depending on the ImageRenderInfo option)
		if (keyBindInfo.ImageRenderInfo == ImageRenderInfo::OnlyIrradiance)
		{
			irradiance = pLight->GetCalculatedIrradianceColor(hitRecord);
			finalColor += irradiance;
		}
		else if (keyBindInfo.ImageRenderInfo == ImageRenderInfo::OnlyBRDF)
		{
			BRDF = pMaterial->Shade(hitRecord, pLight->GetDirection(hitRecord), -cameraRay.Direction);
			finalColor += BRDF;
		}
		else if (keyBindInfo.ImageRenderInfo == ImageRenderInfo::All)
		{
			irradiance = pLight->GetCalculatedIrradianceColor(hitRecord);
			BRDF = pMaterial->Shade(hitRecord, pLight->GetDirection(hitRecord), -cameraRay.Direction);
			finalColor += irradiance * BRDF;
		}
	}

	return finalColor;
}
