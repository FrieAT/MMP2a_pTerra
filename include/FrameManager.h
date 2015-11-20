#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IFrameObserver.h"

class FrameManager
{
public:
	static void Update(sf::RenderWindow* window);
	static void RegisterEventObserver(IFrameObserver* observer);
	static void UnregisterEventObserver(IFrameObserver* observer);
    static void UnregisterAllEventObserver();
private:
	static sf::Clock clock_time;
	static std::vector<IFrameObserver*> Observers;
	static void UpdateEventObserver(sf::Time delta_time);
};
