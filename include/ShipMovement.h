#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"

#include "IPosition.h"
#include "GameObject.h"

class ShipMovement : public IMovement, public IInputObserver, public IFrameObserver
{
public:
	ShipMovement();
	~ShipMovement();
	void MoveVector(sf::Vector2f &Vector);
	void OnInputUpdate(std::string event);
	void OnFrameUpdate(sf::Time delta_time);
private:
	sf::Vector2f direction;
	float acceleration;
};

