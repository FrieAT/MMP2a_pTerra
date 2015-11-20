#include "FrameManager.h"
#include <memory>

std::vector<IFrameObserver*> FrameManager::Observers;
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
	Observers.push_back(observer);
}

void FrameManager::UnregisterEventObserver(IFrameObserver* observer)
{
    for(int i = 0; i < Observers.size(); i++)
    {
        if(Observers[i] != observer) continue;
        Observers.erase(Observers.begin() + i);
        break;
    }
}

void FrameManager::UnregisterAllEventObserver()
{
    Observers.clear();
}