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
    std::shared_ptr<IPosition> Position;
    std::shared_ptr<IMovement> Movement;
    std::shared_ptr<IDrawing> Drawing;
};
