#pragma once

#include <SFML/Graphics.hpp>

class IEventObserver
{
public:
	virtual void OnEventUpdate(sf::Event event) = 0;
};