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
 //   LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	//LinearMovement(float fRotation, float fSpeed);
	LinearMovement(float fRotation, float fSpeed, float fmass, sf::Vector2f fStartSpeed = sf::Vector2f(0,0), bool bAccelerating = false);
    ~LinearMovement();
    void Init();
    void OnFrameUpdate(sf::Time DeltaTime);
    void Serialize(SerializeNode* pParentNode);
	float m_fSpeed;
	float m_fMaxSpeed;

private:
	sf::Vector2f m_Direction;
	float m_fRotation;
	bool m_bAccelerating;
};
