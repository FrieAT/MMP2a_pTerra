/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class ICollisionEventObserver
{
public:
    ~ICollisionEventObserver() { }
    virtual void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact) = 0;
};