#pragma once

#include <SFML/Graphics.hpp>

#include "IViewObserver.h"

class ViewManager
{
public:
    ViewManager() = delete;
    static void Update(sf::Time deltaTime);
    static void Draw(sf::RenderWindow* window);
    static void RegisterEventObserver(IViewObserver* observer);
    static void UnregisterEventObserver(IViewObserver* observer);
private:
    static std::vector<IViewObserver*> Observers;
};