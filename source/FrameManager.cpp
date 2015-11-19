#include "FrameManager.h"
#include <memory>

std::vector<std::shared_ptr<IFrameObserver>> FrameManager::Observers = *new std::vector<std::shared_ptr<IFrameObserver>>();
sf::Clock FrameManager::clock_time;

void FrameManager::Update(sf::RenderWindow* window)
{
	sf::Time dt = clock_time.restart();
	UpdateEventObserver(dt);
}

void FrameManager::UpdateEventObserver(sf::Time delta_time)
{
	for (unsigned int i = 0; i < Observers.size(); i++)
	{
		Observers[i]->OnFrameUpdate(delta_time);
	}
}

void FrameManager::RegisterEventObserver(IFrameObserver* observer)
{
	std::shared_ptr<IFrameObserver> ref (observer);
	Observers.push_back(ref);
}

void FrameManager::UnregisterEventObserver(IFrameObserver* observer)
{
    auto it = FrameManager::Observers.begin();
    while(it != FrameManager::Observers.end())
	{
        if (it->get() == observer)
        {
            FrameManager::Observers.erase(it);
        }
        it++;
	}
}