#pragma once

#include <SFML/Graphics.hpp>

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"

class LinearMovement : public IMovement, public IFrameObserver
{
public:
    LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	LinearMovement(float fRotation, float fSpeed);

    ~LinearMovement();
    void OnFrameUpdate(sf::Time DeltaTime);
	float m_fSpeed;

private:
	sf::Vector2f m_Direction;
	sf::Vector2f m_Movement;

	float m_fRotation;
};
