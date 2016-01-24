/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IEngine.h"
#include "IFrameObserver.h"

class EngineEnergy : public IEngine, public IFrameObserver
{
public:
	EngineEnergy(float fMaxFuel, float fFuel = 0.f);
	~EngineEnergy();
	void Init();
	float GetFuel();
	float GetMaxFuel();
	void AddFuel(float fAddFuel);
	void OnFrameUpdate(sf::Time DeltaTime);
	void Serialize(SerializeNode* pParentNode);
	static IComponent* Deserialize(SerializeNode* pNode);
	std::string GetComponentName() { return std::string("EngineEnergy"); }
private:
	float m_fEnergy;
	float m_fMaxEnergy;
	sf::Clock m_LastDrained;
};