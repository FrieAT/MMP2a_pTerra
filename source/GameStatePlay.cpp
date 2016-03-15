/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "Game.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "FrameManager.h"
#include "AIManager.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include "IHealth.h"

#include "eventbus/EventBus.hpp"
#include "GUIPlayerStatus.h"
#include "PlayerDamageEvent.h"
#include "PlayerFuelEvent.h"

GameStatePlay::~GameStatePlay()
{
    
}

void GameStatePlay::Init(sf::RenderWindow* pWindow)
{
    // Generate new World :D
    WorldManager::GetInstance().GenerateWorld();
    
	// Generate Player
    GameObject* player = GameObjectFactory::CreatePlayerShip(sf::Vector2f(0.f, 0.f), '2');
	IHealth* playerHealth = static_cast<IHealth*>(player->GetComponent(EComponentType::Health));
	playerHealth->SetShield(100.f);

	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

	GUIPlayerStatus* playerStatus = new GUIPlayerStatus(m_Gui);
	EventBus::AddHandler<PlayerDamageEvent>(playerStatus);
	EventBus::AddHandler<PlayerShieldRegenerationEvent>(playerStatus);
	EventBus::AddHandler<ScoreEvent>(playerStatus);
	EventBus::AddHandler<PlayerFuelEvent>(playerStatus);
	EventBus::AddHandler<TimerEvent>(playerStatus);
	GUIManager::GetInstance().AddGUI(playerStatus);
}

void GameStatePlay::SetLoadGame(std::string strLoadGame)
{
    m_strLoadGame = strLoadGame;
    
    // Clear everything.
    ObjectManager::GetInstance().Clear();
    WorldManager::GetInstance().Clear();
    FrameManager::GetInstance().Clear();
    InputManager::GetInstance().Clear();
    CollisionManager::GetInstance().Clear();
    
    // Load the save-game
    WorldManager::GetInstance().LoadGame(m_strLoadGame);
    
    // Refresh cache for generating world upon seed from save-game.
    WorldManager::GetInstance().GenerateWorld();
}

void GameStatePlay::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	pWindow->setMouseCursorVisible(false);

	// Reset keep in GameStateStorage
	bClearOnGameStateChange = true;

	// Manager updates
	FrameManager::GetInstance().Update(DeltaTime);
	InputManager::GetInstance().Update(pWindow, &m_Gui);
	ObjectManager::GetInstance().Update(DeltaTime);
	CollisionManager::GetInstance().Update(DeltaTime);
	AIManager::GetInstance().Update(DeltaTime);
	GUIManager::GetInstance().Update(DeltaTime);
	SoundManager::GetInstance().Update();

	// Rendering
	ObjectManager::GetInstance().Draw(pWindow);
    FrameManager::GetInstance().Draw(pWindow);
	m_Gui.draw();
	//WorldManager::GetInstance().Draw(pWindow); DEBUG
}