/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IFrameObserver.h"
#include "GameObject.h"

class FrameManager
{
public:
	static FrameManager& GetInstance()
	{
		static FrameManager g_Instance;
		return g_Instance;
	}
	void Update(sf::Time DeltaTime);
    void Draw(sf::RenderWindow* pWindow);
	void RegisterEventObserver(IFrameObserver* pObserver);
	void UnregisterEventObserver(IFrameObserver* pObserver);
	void Clear();
private:
	FrameManager() { }
	FrameManager(const FrameManager&) = delete;
	void operator= (const FrameManager&) = delete;
    std::map<GameObject*, std::vector<IFrameObserver*>> m_Observers;
};
