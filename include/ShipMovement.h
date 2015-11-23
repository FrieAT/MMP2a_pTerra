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
	void OnInputUpdate(std::string event);
	void OnFrameUpdate(sf::Time delta_time);
	void update_movement();

	std::vector<sf::Vector2f> Impulses;
	float Acceleration;
	float Max_Speed;	//speedlimit if movement_vec.lenght > Max_Speed -> Damp 

private:
	sf::Vector2f direction;
};

