#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"

class LinearMovement : public IMovement, public IFrameObserver
{
public:
    LinearMovement(float Rotation, sf::Vector2f Shipspeed);
    ~LinearMovement();
    void OnFrameUpdate(sf::Time delta_time);
	float speed;

private:
	sf::Vector2f direction;
	sf::Vector2f movement;

	float rotation;
};
