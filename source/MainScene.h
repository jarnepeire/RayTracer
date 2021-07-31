#pragma once
#include "Scene.h"

class MainScene final : public Scene
{
public:
	MainScene(SDL_Window* pWindow, const std::string& sceneTag = "");
	virtual ~MainScene() = default;

	void Initialize() override;
	void Update(float deltaT) override;
	void Render() override;

	virtual void DisplayKeyBindInfo() const override;
private:
	size_t m_IndexLeftPointLight;
	size_t m_IndexRightPointLight;
	size_t m_IndexDirectionalLight;

	void AddPrimitives();
	void AddLights();
	void AddMaterials();
	void UpdateKeyBindInfo();
};

