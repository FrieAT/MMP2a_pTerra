#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "IEventObserver.h"

class EventManager
{
public:
	static void Update(sf::RenderWindow &window);

	static void RegisterEventObserver(IEventObserver &observer);
	static void UnregisterEventObserver(IEventObserver &observer);

private:
	static std::vector<std::shared_ptr<IEventObserver>> Observers;
	static void UpdateEventObserver(sf::Event event);
};
