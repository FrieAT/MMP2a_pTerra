//
//  GameObject.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <exception>

#include "EComponentType.h"

class IComponent;

class GameObject
{
public:
    GameObject();
    ~GameObject();
    
    void SetComponent(std::shared_ptr<IComponent> component);
    void RemoveComponent(EComponentType component_type);
    std::shared_ptr<IComponent> GetComponent(EComponentType component_type);
    
private:
    std::map<EComponentType,std::shared_ptr<IComponent>> Components;
};

#endif /* GameObject_h */
