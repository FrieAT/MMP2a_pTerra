#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"

class LinearMovement : public IMovement, public IInputObserver, public IFrameObserver
{
public:
	LinearMovement();
	void MoveVector(sf::Vector2f &Vector);
	void OnInputUpdate(sf::Event event);
	void OnFrameUpdate(sf::Time delta_time);
private:
	float MovementX;
	float MovementY;
};
