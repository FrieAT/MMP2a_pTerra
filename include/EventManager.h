#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IEventObserver.h"

class EventManager
{
public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}
	void Update(sf::Time deltaTime);
	void RegisterEventObserver(IEventObserver* observer);
	void UnregisterEventObserver(IEventObserver* observer);
    void UnregisterAllEventObserver();
private:
	EventManager() {}
	EventManager(EventManager const&) = delete;
	void operator= (EventManager const&) = delete;
	std::vector<IEventObserver*> Observers;
	void UpdateEventObserver(sf::Event event);
};
