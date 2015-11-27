/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "GameObject.h"

#include "IPosition.h"
#include "IMovement.h"
#include "IDrawing.h"

class GameObjectFactory
{
public:
	GameObjectFactory() = delete;
	~GameObjectFactory() = delete;
	static GameObject* CreatePlayerShip(sf::Vector2f Position, char cPlayer);
	static GameObject* CreateMissile(IPosition* pPosition, sf::Vector2f ShipSpeed);
	static GameObject* CreateAsteroid(sf::Vector2f vPosition, float fRotation, float fSpeed);

    static GameObject* CreateBackgroundSprite(std::string strBackgroundPath);
    static GameObject* CreateBackgroundSprite(std::string strBackgroundPath, sf::Vector2f ScaleTo);
    static GameObject* CreateFontText(sf::Vector2f Position, std::string strFontPath, std::string strText, int iCharSize);
};

