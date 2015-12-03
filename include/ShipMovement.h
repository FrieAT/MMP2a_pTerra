#pragma once

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
	ShipMovement(char cPlayer);
	~ShipMovement();
	void OnInputUpdate(std::string strEvent);
	void OnFrameUpdate(sf::Time DeltaTime);
	void UpdateMovement();
	sf::Vector2f GetMovementVector();
	char m_cPlayer;

	std::vector<sf::Vector2f> m_Impulses; // SET PRIVATE!
	float m_fAcceleration;
	float m_fMaxSpeed;	//speedlimit if movement_vec.lenght > Max_Speed -> Damp
	float m_fFirerate;

private:
	sf::Vector2f m_Direction;
	std::vector<bool> m_shipstates;
	float m_fWeaponcoolDown;
};

