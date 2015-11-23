#pragma once

#include <SFML/Graphics.hpp>

class IFrameObserver
{
public:
    ~IFrameObserver() { }
    virtual void OnFrameUpdate(sf::Time delta_time) { }
    virtual void OnFrameDraw(sf::RenderWindow* window) { }
};
