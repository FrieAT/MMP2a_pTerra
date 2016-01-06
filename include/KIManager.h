/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include "IKI.h"
#include "IKIObserver.h"

class KIManager
{
public:
	static KIManager& GetInstance()
	{
		static KIManager g_Instance;
		return g_Instance;
	}
	void Update(sf::Time DeltaTime);
	void RegisterKIObserver(IKIObserver* pObserver);
	void UnregisterKIObserver(IKIObserver* pObserver);
	void Clear();
private:
	KIManager() { }
	KIManager(const KIManager&) = delete;
	void operator= (const KIManager&) = delete;
	std::vector<IKIObserver*> m_Observers;

};
