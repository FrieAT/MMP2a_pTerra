#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "IInputObserver.h"


class InputManager
{
public:
	static void Update(sf::RenderWindow* window);
	static void RegisterEventObserver(IInputObserver* observer);
	static void UnregisterEventObserver(IInputObserver* observer);

private:
	static std::vector<std::shared_ptr<IInputObserver>> Observers;
	static void UpdateEventObserver(std::string event);
};
