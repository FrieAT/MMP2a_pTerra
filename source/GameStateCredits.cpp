/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "GameStateCredits.h"
#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "SpriteDrawing.h"
#include "WorldManager.h"
#include "IScore.h"

GameStateCredits::~GameStateCredits()
{
	m_Gui.removeAllWidgets();
}

void GameStateCredits::Init(sf::RenderWindow* pWindow)
{
	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

	// Create GUI for this GameState
	// Credits header label
	auto labelCreditsHeader = std::make_shared<tgui::Label>();
	labelCreditsHeader->setText("Credits");
	labelCreditsHeader->setTextSize(100);
	labelCreditsHeader->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(labelCreditsHeader) / 2, 50.f);
	labelCreditsHeader->setTextColor(sf::Color::White);
	m_Gui.add(labelCreditsHeader, "labelCreditsHeader");

	// Credits
	auto labelCredits = std::make_shared<tgui::Label>();
	labelCredits->setText("Programmers\n\tFriedle Andreas\n\tSchmidt Friedrich\n\tStadlberger Florian\n\nArtists\n\tLilee Neururer\n\nSoundeffects\n\thttp://soundbible.com/1151-Grenade.html\n\tMike Koenig - Attributon 3.0 (Licence)\n\n\thttp://soundbible.com/1950-Button-Push.html\n\tMike Koenig - Attributon 3.0 (Licence)\n\n\thttp://soundbible.com/838-Censor-Beep.html\n\tMike Koenig - Attributon 3.0 (Licence)");
	labelCredits->setTextSize(20);
	labelCredits->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(labelCredits) / 2, 250.f);
	labelCredits->setTextColor(sf::Color::White);
	m_Gui.add(labelCredits, "labelCredits");

	// Menu button
	tgui::Button::Ptr buttonMenu = theme->load("Button"); // Verwenden von Theme für Button
	buttonMenu->setText("Back to Main Menu");
	buttonMenu->setTextSize(28);
	buttonMenu->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonMenu) / 2, 800.f);
	buttonMenu->connect("clicked", []() {
		SoundManager::GetInstance().PlaySoundClick();
		Game::m_pEngine->ChangeState(EGameState::GameStateIntro);
	});
	m_Gui.add(buttonMenu, "buttonMenu");
}

void GameStateCredits::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
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