/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "Game.h"
#include "GameStatePause.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "FrameManager.h"
#include "GameStatePlay.h"

GameStatePause::~GameStatePause()
{
	m_Gui.removeAllWidgets();
}

void GameStatePause::Init(sf::RenderWindow* pWindow)
{
	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

	// Create GUI for this GameState
	// Continue button
	tgui::Button::Ptr buttonContinue = theme->load("Button"); // Verwenden von Theme für Button
	buttonContinue->setText("Continue");
	buttonContinue->setTextSize(28);
	buttonContinue->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonContinue) / 2, 200.f);
	buttonContinue->connect("clicked", []() { 
		Game::m_pEngine->ChangeState(EGameState::GameStatePlay);
	});
	m_Gui.add(buttonContinue, "buttonContinue");

	// Menu button
	tgui::Button::Ptr buttonMenu = theme->load("Button"); // Verwenden von Theme für Button
	buttonMenu->setText("Main Menu");
	buttonMenu->setTextSize(28);
	buttonMenu->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonMenu) / 2, 400.f);
	buttonMenu->connect("clicked", []() {
		Game::m_pEngine->ChangeState(EGameState::GameStatePlay);
		GameStatePlay* pPlayState = dynamic_cast<GameStatePlay*>(Game::m_pEngine->GetLastState());
		if (pPlayState != nullptr)
		{
			WorldManager::GetInstance().SaveGame("savegame.txt");
		}
		Game::m_pEngine->ChangeState(EGameState::GameStateIntro);
	});
	m_Gui.add(buttonMenu, "buttonMenu");
}

void GameStatePause::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// No managers, give Events directly to Gui
	sf::Event Event;
	while (pWindow->pollEvent(Event))
	{
		m_Gui.handleEvent(Event);
	}

	// Rendering
	FrameManager::GetInstance().Draw(pWindow);
	ObjectManager::GetInstance().Draw(pWindow);
	m_Gui.draw();
}