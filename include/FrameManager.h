#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IFrameObserver.h"

class FrameManager
{
public:
	FrameManager() = delete;
	static void Update(sf::Time deltaTime);
    static void Draw(sf::RenderWindow* window);
	static void RegisterEventObserver(IFrameObserver* observer);
	static void UnregisterEventObserver(IFrameObserver* observer);
	static void Clear();
private:
	static std::vector<IFrameObserver*> Observers;
};
