/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include "IAI.h"
#include "IAIObserver.h"

class AIManager
{
public:
	static AIManager& GetInstance()
	{
		static AIManager g_Instance;
		return g_Instance;
	}
	void Update(sf::Time DeltaTime);
	void RegisterKIObserver(IAIObserver* pObserver);
	void UnregisterKIObserver(IAIObserver* pObserver);
	void Clear();
private:
	AIManager() { }
	AIManager(const AIManager&) = delete;
	void operator= (const AIManager&) = delete;
	std::vector<IAIObserver*> m_Observers;

};
