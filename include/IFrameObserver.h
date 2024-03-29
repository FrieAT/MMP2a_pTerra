/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

class IFrameObserver
{
public:
    ~IFrameObserver() { }
    virtual void OnFrameUpdate(sf::Time DeltaTime) { }
    virtual void OnFrameDraw(sf::RenderWindow* pWindow) { }
};
