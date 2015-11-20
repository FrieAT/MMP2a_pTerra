#pragma once

#include "GameObject.h"

#include "IPosition.h"
#include "IMovement.h"
#include "IDrawing.h"

class PlayerShip : public GameObject
{
public:
	PlayerShip();
	~PlayerShip();
private:
    IPosition* Position;
    IMovement* Movement;
    IDrawing* Drawing;
};
