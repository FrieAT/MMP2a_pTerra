#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IInputObserver.h"


class InputManager
{
public:
	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}
	void Update(sf::RenderWindow* window);
	void RegisterEventObserver(IInputObserver* observer);
	void UnregisterEventObserver(IInputObserver* observer);
	void Clear();
private:
	InputManager() {}
	InputManager(InputManager const&) = delete;
	void operator= (InputManager const&) = delete;
	std::vector<IInputObserver*> Observers;
	void UpdateEventObserver(std::string event);
};
