//
//  ObjectManager.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>

#include "IManager.h"
#include "IDrawing.h"

#include "GameObject.h"

class ObjectManager : public IManager
{
public:
    static void AddGameObject(GameObject &obj);
    static void RemoveGameObject(GameObject &obj);
    static void Update(sf::RenderWindow &window);
private:
    static std::vector<std::shared_ptr<GameObject>> Objects;
};

#endif /* ObjectManager_h */
