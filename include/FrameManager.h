#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IFrameObserver.h"

class FrameManager
{
public:
	static void Update(sf::Time deltaTime);
	static void RegisterEventObserver(IFrameObserver* observer);
	static void UnregisterEventObserver(IFrameObserver* observer);
    static void UnregisterAllEventObserver();
private:
	static std::vector<IFrameObserver*> Observers;
	static void UpdateEventObserver(sf::Time deltaTime);
};
