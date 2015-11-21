#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IInputObserver.h"


class InputManager
{
public:
	InputManager() = delete;
	static void Update(sf::RenderWindow* window);
	static void RegisterEventObserver(IInputObserver* observer);
	static void UnregisterEventObserver(IInputObserver* observer);
    static void UnregisterAllEventObserver();
    static std::vector<IInputObserver*> Observers;
private:
	
	static void UpdateEventObserver(std::string event);
};
