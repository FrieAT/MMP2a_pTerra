/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"
#include "ICollisionEventObserver.h"

class HealthExplosion : public IHealth, public IFrameObserver
{
public:
    HealthExplosion(float fHealth);
    ~HealthExplosion();
    void Init();
    void Damage(float fDamage);
    void OnFrameUpdate(sf::Time DeltaTime);
    std::string GetComponentName() { return std::string("HealthExplosion"); }
    static IComponent* Deserialize(SerializeNode* pNode);
private:
    
};