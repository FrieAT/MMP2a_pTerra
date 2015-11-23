#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IFrameObserver.h"

class FrameManager
{
public:
	static FrameManager& GetInstance()
	{
		static FrameManager instance;
		return instance;
	}
	void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow* window);
	void RegisterEventObserver(IFrameObserver* observer);
	void UnregisterEventObserver(IFrameObserver* observer);
	void Clear();
private:
	FrameManager() {}
	FrameManager(FrameManager const&) = delete;
	void operator= (FrameManager const&) = delete;
	std::vector<IFrameObserver*> Observers;
};
