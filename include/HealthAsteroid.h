/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"
#include "ICollisionEventObserver.h"

class HealthAsteroid : public IHealth , public IFrameObserver, public ICollisionEventObserver
{
public:
    HealthAsteroid(float fHealth);
    ~HealthAsteroid();
    void Init();
    void Damage(float fDamage);
    void OnFrameDraw(sf::RenderWindow* pWindow);
    void OnFrameUpdate(sf::Time DeltaTime);
    void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact);
private:
    GameObject* m_pHealthDebug;
};