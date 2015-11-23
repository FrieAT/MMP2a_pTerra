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
	static GameObject* CreatePlayerShip(sf::Vector2f Position);
    static GameObject* CreateBackgroundSprite(std::string background_path);
    static GameObject* CreateBackgroundSprite(std::string background_path, sf::Vector2f scaleTo);
    static GameObject* CreateFontText(sf::Vector2f Position, std::string sFontPath, std::string sText, int iCharSize);
};

