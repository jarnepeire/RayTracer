#pragma once
#include <string>
#include "Structs.h"
#include "InputManager.h"
#include "MaterialManager.h"
#include "PrimitiveManager.h"
#include "LightManager.h"

namespace Elite
{
	class Renderer;
}

struct SDL_Window;
class SceneManager;
class Primitive;
class Light;
class Material;
class Camera;

class Scene
{
public:
	Scene(SDL_Window* pWindow, const std::string& sceneTag);
	Scene(const Scene& s) = delete;
	Scene(Scene&& s) = delete;
	Scene& operator=(const Scene& s) = delete;
	Scene& operator=(Scene&& s) = delete;
	virtual ~Scene();

	/* Initialize the scene and its objects */
	virtual void Initialize() = 0;

	/* Update the scene (track input, update primitives..) */
	virtual void Update(float deltaT) = 0;

	/* Render the scene and its objects */
	virtual void Render() = 0;

	/* Returns pointer to the renderer of the scene */
	Elite::Renderer* GetRenderer() const { return m_pRenderer; }
	
	/* Returns pointer to the primitive manager */
	const PrimitiveManager& GetPrimitiveManager() const { return m_PrimitiveManager; }
	
	/* Return pointer to the light manager */
	const LightManager& GetLightManager() const { return m_LightManager; }
	
	/* Return pointer to the material manager */
	const MaterialManager& GetMaterialManager() const { return m_MaterialManager; }
	
	/* Return pointer to the camera of this scene */
	Camera* GetCamera() const { return m_pCamera; }

	/* Returns reference to input manager that tracks mouse- and keyboard input */
	const InputManager& GetInput() const { return m_Input; }

	/* Return const reference to key bind information object */
	const KeyBindInfo& GetKeyBindInfo() const { return m_KeyBindInfo; }

	/* Return reference to the scene's tag */
	const std::string& GetSceneTag() const { return m_SceneTag; }

	/* Return the scene's index */
	int GetSceneIndex() const { return m_SceneIndex; }

protected:
	/* Unique scene information */
	int m_SceneIndex;
	const std::string m_SceneTag;

	/* Window info */
	int m_Height;
	int m_Width;

	KeyBindInfo m_KeyBindInfo;
	std::string m_FirstSpaces;
	std::string m_LastSpaces;
	virtual void DisplayKeyBindInfo() const = 0;

	/* Adding objects to scene */
	void AddPrimitive(Primitive* primitive);
	size_t AddLight(Light* pLight);
	void AddMaterial(Material* pMaterial);

private:
	/* For access to root functionality (RootInitialize(), RootUpdate()..) */
	friend class SceneManager;
	
	Elite::Renderer* m_pRenderer;
	Camera* m_pCamera;

	InputManager m_Input;
	PrimitiveManager m_PrimitiveManager;
	LightManager m_LightManager;
	MaterialManager m_MaterialManager;
	
	unsigned int m_TotalWhiteSpaces;

	/* Private functions */
	void RootInitialize();
	void RootUpdate(float deltaT);
	void RootRender();
	void InitializeSpacingForKeybindInfo();
	void SetSceneIndex(int sceneIdx);
};
