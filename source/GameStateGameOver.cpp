/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "GameStateGameOver.h"
#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "SpriteDrawing.h"
#include "WorldManager.h"
#include "IScore.h"
#include "SoundManager.h"
#include "INavigation.h"

GameStateGameOver::~GameStateGameOver()
{
	m_Gui.removeAllWidgets();
}

void GameStateGameOver::Init(sf::RenderWindow* pWindow)
{
	// Remove the savegame
	std::remove("savegame.txt");

	GameObject* pPlayer = ObjectManager::GetInstance().GetPlayer();
	INavigation* pNavigation = static_cast<INavigation*>(pPlayer->GetComponent(EComponentType::Navigation));
	bool foundTerra = pNavigation->FoundTerra();

	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

	// Create GUI for this GameState
	// Background Terra for winning
	if (foundTerra)
	{
		auto terraBackground = std::make_shared<tgui::Picture>("assets/lilee/planet_earth.png");
		terraBackground->move(tgui::Layout2d(-55, -900));
		m_Gui.add(terraBackground);
		terraBackground->moveToBack();
	}

	// Game Over label
	auto labelGameOver = std::make_shared<tgui::Label>();
	if (foundTerra)
	{
		labelGameOver->setText("You won");
	}
	else
	{
		labelGameOver->setText("Game over");
	}
	labelGameOver->setTextSize(100);
	labelGameOver->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(labelGameOver) / 2, 100.f);
	labelGameOver->setTextColor(sf::Color::White);
	m_Gui.add(labelGameOver, "labelGameOver");

	// Score label
	if (pPlayer != nullptr)
	{
		IScore* pScore = static_cast<IScore*>(pPlayer->GetComponent(EComponentType::Score));
		if (pScore != nullptr)
		{
			auto labelGameOver = std::make_shared<tgui::Label>();
			labelGameOver->setText("Score: "+std::to_string(pScore->GetScore())+" Points");
			labelGameOver->setTextSize(40);
			labelGameOver->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(labelGameOver) / 2, 300.f);
			labelGameOver->setTextColor(sf::Color::White);
			m_Gui.add(labelGameOver, "labelGameOver");
		}
	}

	// Menu button
	tgui::Button::Ptr buttonMenu = theme->load("Button"); // Verwenden von Theme für Button
	buttonMenu->setText("Back to Main Menu");
	buttonMenu->setTextSize(28);
	buttonMenu->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonMenu) / 2, 500.f);
	buttonMenu->connect("clicked", []() {
		SoundManager::GetInstance().PlaySoundClick();
		Game::m_pEngine->ChangeState(EGameState::GameStateIntro);
	});
	m_Gui.add(buttonMenu, "buttonMenu");
}

void GameStateGameOver::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// No managers, give Events directly to Gui
	sf::Event Event;
	while (pWindow->pollEvent(Event))
	{
		m_Gui.handleEvent(Event);
	}

	// Drawing
	m_Gui.draw();
}