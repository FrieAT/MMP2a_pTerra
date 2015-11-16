//
//  IComponent.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IComponent_h
#define IComponent_h

#include <memory>

#include <SFML/Graphics.hpp>

#include "EComponentType.h"

class GameObject;

class IComponent
{
public:
    virtual EComponentType GetComponentType() = 0;
    void SetAssignedGameObject(GameObject &obj) {
        GameObj = &obj;
    }
    GameObject* GetAssignedGameObject() {
        return GameObj;
    }
private:
    GameObject* GameObj;
};

#endif /* IComponent_h */
