#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IEventObserver.h"

class EventManager
{
public:
	static void Update(sf::Time deltaTime);
	static void RegisterEventObserver(IEventObserver* observer);
	static void UnregisterEventObserver(IEventObserver* observer);
    static void UnregisterAllEventObserver();
private:
	static std::vector<IEventObserver*> Observers;
	static void UpdateEventObserver(sf::Event event);
};
