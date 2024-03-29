/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "GameObjectFactory.h"
#include "Game.h"
#include "LinearMovement.h"
#include "SpriteDrawing.h"
#include "PixelPosition.h"
#include "QuadrantPosition.h"
#include "FontDrawing.h"
#include "ShipMovement.h"
#include "StaticView.h"
#include "DynamicView.h"
#include "HealthShip.h"
#include "HealthMissile.h"
#include "HealthAsteroid.h"
#include "HealthExplosion.h"
#include "CircleCollision.h"
#include "BoxCollision.h"
#include "NavigationCursor.h"
#include "ResearchScore.h"
#include "SimpleAI.h"
#include "LogicScore.h"
#include "LogicTime.h"
#include "EngineEnergy.h"

GameObject* GameObjectFactory::CreatePlayerShip(sf::Vector2f Position, char cPlayer)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pShip = new GameObject(std::string("ship"));
	pShip->SetComponent(new QuadrantPosition(sf::Vector2f(Position), sf::Vector2f(32.f, 51.f)));
	pShip->SetComponent(new ShipMovement(cPlayer));
    SpriteDrawing* pSpriteComponent = new SpriteDrawing(std::string("assets/ship_player.png"), sf::Vector2f(192.f, 128.f));
    pSpriteComponent->SetUpdateFrameRate(20);
    pSpriteComponent->SetTextureArea(sf::FloatRect(0.f, 0.f, 64.f, 102.f));
    pShip->SetComponent(pSpriteComponent);
    
	// Create view and add event handler for screen shake
	DynamicView* playerView = new DynamicView(sf::FloatRect(0, 0, static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)), sf::Vector2f(1920.f - static_cast<float>(Game::m_iWindowWidth), 0));
	pShip->SetComponent(playerView);
	
	pShip->SetComponent(new BoxCollision(64.f, 102.f));
    pShip->SetComponent(new HealthShip(100.f));
    pShip->SetComponent(new NavigationCursor());
    pShip->SetComponent(new ResearchScore(50, 100));
	pShip->SetComponent(new LogicTime(10 * 60)); // 10 Minuten GameTime
	pShip->SetComponent(new EngineEnergy(100.f, 40.f));
	return pShip;
}

GameObject * GameObjectFactory::CreateEnemyShip(sf::Vector2f Position)
{
	GameObject* pShip = new GameObject(std::string("enemyship"));
	pShip->SetComponent(new PixelPosition(sf::Vector2f(Position), sf::Vector2f(32.f, 51.f)));
	ShipMovement* aimove = new ShipMovement('E');
	aimove->SetMass(8);
	aimove->SetFirerate(1.0f);
	pShip->SetComponent(aimove);
	SpriteDrawing* pSpriteComponent = new SpriteDrawing(std::string("assets/ship_regierung.png"), sf::Vector2f(192.f, 128.f));
	pSpriteComponent->SetTextureArea(sf::FloatRect(0.f, 0.f, 64.f, 102.f));
	pShip->SetComponent(pSpriteComponent);
	//pShip->SetComponent(new DynamicView(sf::FloatRect(0, 0, static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)), sf::Vector2f(1920.f - static_cast<float>(Game::m_iWindowWidth), 0), 20.f));
	//pShip->SetComponent(new CircleCollision(30.f,pos));
	pShip->SetComponent(new SimpleAI());
	pShip->SetComponent(new BoxCollision(64, 100));
	pShip->SetComponent(new HealthAsteroid(150.f));
	ResearchScore* pScoreComponent = new ResearchScore(9999999, 9999999);
	pScoreComponent->SetScore(200 + rand() % 300);
	pShip->SetComponent(new EngineEnergy(1000.f, 1000.f));
	pShip->SetComponent(pScoreComponent);
	return pShip;
}

GameObject* GameObjectFactory::CreateMissile(GameObject* pOwner, IPosition* pPosition, sf::Vector2f ShipSpeed)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pMissile = new GameObject(std::string("missile"));
    BoxCollision* pCollisision = new BoxCollision(30, 60);
    
    pCollisision->m_bPhysicsApplyable = false;
    
	pMissile->SetComponent(new HealthMissile(10, pOwner));
	pMissile->SetComponent(new PixelPosition(pPosition->GetPosition(), sf::Vector2f(15.f, 30.f)));
	pMissile->SetComponent(new LinearMovement(pPosition->GetRotation(), 800.f, 1.f, ShipSpeed, true));
    SpriteDrawing* pSpriteComponent = new SpriteDrawing(std::string("assets/rakete_player.png"),sf::Vector2f(30,60));
    pSpriteComponent->SetTextureArea(sf::FloatRect(96.f, 0.f, 96.f, 899.f));
    pSpriteComponent->SetTextureArea(sf::FloatRect(192.f, 0.f, 96.f, 899.f));
	pMissile->SetComponent(pSpriteComponent);
    pMissile->SetComponent(pCollisision);
    
	return pMissile;
}

GameObject* GameObjectFactory::CreateAsteroid(sf::Vector2f vPosition, float fRotation, float fSpeed)
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* pAsteroid = new GameObject(std::string("asteroid"));
	pAsteroid->SetComponent(new PixelPosition(vPosition, sf::Vector2f(35.f, 30.f)));
	pAsteroid->SetComponent(new LinearMovement(fRotation, fSpeed,15));
	pAsteroid->SetComponent(new SpriteDrawing(std::string("assets/asteroid.png"), sf::Vector2f(70.f, 60.f)));
	//pAsteroid->SetComponent(new CircleCollision(40.f, pos));
	pAsteroid->SetComponent(new BoxCollision(70.f, 70.f));
	pAsteroid->SetComponent(new HealthAsteroid(100.f));
    ResearchScore* pScoreComponent = new ResearchScore(9999999, 9999999);
    pScoreComponent->SetScore(rand() % 100);
    pAsteroid->SetComponent(pScoreComponent);
	return pAsteroid;
}

GameObject* GameObjectFactory::CreateBackgroundSprite(std::string strBackgroundPath)
{
    // TODO: Make it possible to change component values / change the whole factory
    GameObject* pBackground = new GameObject(std::string("background"));
    
    pBackground->SetComponent(new QuadrantPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    pBackground->SetComponent(new SpriteDrawing(strBackgroundPath));
    
    return pBackground;
}
GameObject* GameObjectFactory::CreateBackgroundSprite(std::string strBackgroundPath, sf::Vector2f ScaleTo)
{
	GameObject* pBackground = new GameObject(std::string("background"));
    
	pBackground->SetComponent(new QuadrantPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    pBackground->SetComponent(new SpriteDrawing(strBackgroundPath, ScaleTo));
    
    return pBackground;
}

GameObject* GameObjectFactory::CreateBackgroundSprite(std::string strBackgroundPath, sf::Vector2f Position, sf::Vector2f ScaleTo)
{
    GameObject* pBackground = new GameObject(std::string("background"));
    
    pBackground->SetComponent(new PixelPosition(Position, sf::Vector2f(0.f, 0.f)));
    pBackground->SetComponent(new SpriteDrawing(strBackgroundPath, ScaleTo));
    
    return pBackground;
}

GameObject* GameObjectFactory::CreateExplosion(sf::Vector2f Position)
{
    const int iAmountInXAxis = 6;
    const int iAmountInYAxis = 3;
    
    GameObject* pExplosion = new GameObject("effect");
    pExplosion->SetTemporaryState(true); // Never save explosion´s in save-game´s
    
    pExplosion->SetComponent(new PixelPosition(Position, sf::Vector2f()));
    pExplosion->SetComponent(new HealthExplosion(((iAmountInXAxis * iAmountInYAxis) / (float)Game::m_iFrameRate * 20)));
    SpriteDrawing* pSpriteDrawing = new SpriteDrawing("assets/explosion.png", false);
    pSpriteDrawing->SetUpdateFrameRate(Game::m_iFrameRate);
    pSpriteDrawing->GenerateTextureAreas(iAmountInXAxis, iAmountInYAxis);
    pExplosion->SetComponent(pSpriteDrawing);
    
    return pExplosion;
}

GameObject* GameObjectFactory::CreateFontText(sf::Vector2f Position, std::string strFontPath, std::string strText, int iCharSize)
{
    GameObject* pFontText = new GameObject(std::string("text"));
    
    pFontText->SetComponent(new PixelPosition(Position, sf::Vector2f(0.f, 0.f)));
    pFontText->SetComponent(new FontDrawing(strFontPath, strText, iCharSize));
    
    return pFontText;
}

GameObject* GameObjectFactory::CreatePlanet(sf::Vector2f Position, EWorldObjectType eType)
{
    std::vector<std::string> SpaceStationsRes;
    SpaceStationsRes.push_back("assets/planet_ice.png");
    SpaceStationsRes.push_back("assets/planet_sand.png");
    
    if(eType == EWorldObjectType::Terra)
    {
        SpaceStationsRes.clear();
        SpaceStationsRes.push_back("assets/planet_earth.png");
    }
    
    GameObject* pPlanet = new GameObject(std::string("planet"));
    
    pPlanet->SetComponent(new PixelPosition(Position, sf::Vector2f(1000.f, 1000.f)));
    pPlanet->SetComponent(new SpriteDrawing(SpaceStationsRes[rand() % SpaceStationsRes.size()]));
	pPlanet->SetComponent(new BoxCollision(700.f, 700.f));
	ResearchScore* pScoreComponent = new ResearchScore(9999999, 9999999);
	pScoreComponent->SetScore(100 + rand() % 500);
	pPlanet->SetComponent(pScoreComponent);
	pPlanet->SetComponent(new LogicScore());
    
    return pPlanet;
}