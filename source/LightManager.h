#pragma once
#include <vector>

class Light;
class LightManager final
{
public: 
	LightManager() = default;
	LightManager(const LightManager& lm) = delete;
	LightManager(LightManager&& lm) = delete;
	LightManager& operator=(const LightManager& lm) = delete;
	LightManager& operator=(LightManager&& lm) = delete;
	~LightManager();

	/* Adds a light to the manager and returns the current index this light is held in, 
		In case of invalid light or nullptr -> returns -1 */
	size_t AddLight(Light* pLight);

	/* Return reference to vector of all lights this manager holds */
	/*inline*/ const std::vector<Light*>& GetLights() const { return m_pLights; }
private:
	std::vector<Light*> m_pLights;
};

