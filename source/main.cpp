#pragma once
//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
#include "SceneManager.h"

//Scene includes
#include "MainScene.h"
#include "BunnyScene.h"

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - Jarne Peire",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	SceneManager* pScenegraph = new SceneManager();
	pScenegraph->AddScene(new MainScene(pWindow, "MainScene"));
	pScenegraph->AddScene(new BunnyScene(pWindow, "BunnyScene"));
	pScenegraph->SetActiveScene("MainScene");

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	while (isLooping)
	{
		//--------- Timer ---------
		pTimer->Update();
		float elapsedTime = pTimer->GetElapsed();
		printTimer += elapsedTime;
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		//--------- Update ---------
		pScenegraph->Update(elapsedTime);

		//--------- Render ---------
		pScenegraph->Render();

		//Save screenshot after full render
		auto pScene = pScenegraph->GetCurrentScene();
		const auto& input = pScene->GetInput();
		if (input.IsPressed(EKeyboardInput::TakeScreenshot))
		{
			if (!pScene->GetRenderer()->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
		}

		//Update looping
		isLooping = input.IsLooping();
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pScenegraph;
	delete pTimer;

	ShutDown(pWindow);
	return 0;
}