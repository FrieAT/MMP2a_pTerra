/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "GameObjectFactory.h"
#include "Game.h"
#include "LinearMovement.h"
#include "SpriteDrawing.h"
#include "PixelPosition.h"
#include "QuadrantPosition.h"
#include "FontDrawing.h"
#include "ShipMovement.h"
#include "DynamicView.h"
#include "Shiphealth.h"
#include "Missilehealth.h"
#include "CircleCollision.h"

GameObject* GameObjectFactory::CreatePlayerShip(sf::Vector2f Position, char cPlayer)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pShip = new GameObject(std::string("ship"));
	QuadrantPosition* pos = new QuadrantPosition(sf::Vector2f(Position), sf::Vector2f(32.f, 32.f));
	pShip->SetComponent(pos);
	pShip->SetComponent(new ShipMovement(cPlayer));
	pShip->SetComponent(new SpriteDrawing(std::string("assets/space_ship.png")));
    pShip->SetComponent(new DynamicView(sf::FloatRect(0, 0, static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)), sf::Vector2f(1920.f - static_cast<float>(Game::m_iWindowWidth), 0), 20.f));
    pShip->SetComponent(new CircleCollision(30.f,pos));
    pShip->SetComponent(new Shiphealth(100.f));
	return pShip;
}

GameObject* GameObjectFactory::CreateMissile(IPosition* pPosition, sf::Vector2f ShipSpeed)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pMissile = new GameObject(std::string("missile"));
	pMissile->SetComponent(new Missilehealth(500));
	pMissile->SetComponent(new PixelPosition(pPosition->GetPosition(), sf::Vector2f(160.f, 320.f)));
	pMissile->SetComponent(new LinearMovement(pPosition->GetRotation(),300.f,1,ShipSpeed,true));
	pMissile->SetComponent(new SpriteDrawing(std::string("assets/rocket.png"),sf::Vector2f(30,60)));
	
	return pMissile;
}

GameObject* GameObjectFactory::CreateAsteroid(sf::Vector2f vPosition, float fRotation, float fSpeed)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pAsteroid = new GameObject(std::string("asteroid"));
	PixelPosition* pos = new PixelPosition(vPosition, sf::Vector2f(83.f, 66.5f));
	pAsteroid->SetComponent(pos);
	pAsteroid->SetComponent(new LinearMovement(fRotation, fSpeed,15));
	pAsteroid->SetComponent(new SpriteDrawing(std::string("assets/asteroid.png"),sf::Vector2f(83.f, 66.5f)));
	pAsteroid->SetComponent(new CircleCollision(40.f, pos));

	return pAsteroid;
}

GameObject* GameObjectFactory::CreateBackgroundSprite(std::string strBackgroundPath)
{
    // TODO: Make it possible to change component values / change the whole factory
    GameObject* pBackground = new GameObject(std::string("background"));
    
    pBackground->SetComponent(new PixelPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    pBackground->SetComponent(new SpriteDrawing(strBackgroundPath));
    
    return pBackground;
}
GameObject* GameObjectFactory::CreateBackgroundSprite(std::string strBackgroundPath, sf::Vector2f ScaleTo)
{
	GameObject* pBackground = new GameObject(std::string("background"));
    
	pBackground->SetComponent(new PixelPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    pBackground->SetComponent(new SpriteDrawing(strBackgroundPath, ScaleTo));
    
    return pBackground;
}

GameObject* GameObjectFactory::CreateBackgroundStar(sf::Vector2f Position)
{
    int TextureWidth = 100;
    int TextureHeight = 100;
    int TextureAmountX = 6;
    int TextureAmountY = 3;
    
    int TextureX = (rand() % TextureAmountX) * TextureWidth;
    int TextureY = (rand() % TextureAmountY) * TextureHeight;
    
    GameObject* pStarBackground = new GameObject(std::string("background"));
    SpriteDrawing* pSprite = new SpriteDrawing("assets/Star-Sprites.png", sf::Vector2f(0.f,0.f));
    
    pSprite->SetTextureArea(sf::FloatRect(TextureX, TextureY, TextureWidth, TextureHeight));
    
    pStarBackground->SetComponent(new PixelPosition(Position, sf::Vector2f(0.f, 0.f)));
    pStarBackground->SetComponent(pSprite);
    
    return pStarBackground;
}

GameObject* GameObjectFactory::CreateFontText(sf::Vector2f Position, std::string strFontPath, std::string strText, int iCharSize)
{
    GameObject* pFontText = new GameObject(std::string("text"));
    
    pFontText->SetComponent(new PixelPosition(Position, sf::Vector2f(0.f, 0.f)));
    pFontText->SetComponent(new FontDrawing(strFontPath, strText, iCharSize));
    
    return pFontText;
}