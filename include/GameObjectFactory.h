#pragma once

#include "GameObject.h"

#include "IPosition.h"
#include "IMovement.h"
#include "IDrawing.h"

class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();
	static GameObject* CreatePlayerShip();
};

