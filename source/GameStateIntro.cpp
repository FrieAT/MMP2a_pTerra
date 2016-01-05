/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "GameStateIntro.h"

#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "WorldManager.h"

GameStateIntro::~GameStateIntro()
{
	m_Gui.removeAllWidgets();
    InputManager::GetInstance().UnregisterEventObserver(this);
}

void GameStateIntro::Init(sf::RenderWindow* pWindow)
{
    m_bKeyPressed = false;

	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

	// Create GUI for this GameState
	// Background
	auto background = std::make_shared<tgui::Picture>("assets/intro-bg.jpg");
	background->setSize(Game::m_iWindowWidth, Game::m_iWindowHeight);
	m_Gui.add(background);
	background->moveToBack();

	// Logo
	auto logo = std::make_shared<tgui::Picture>("assets/logo.png");
	logo->scale(0.4f, 0.4f);
	logo->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(logo) / 2, 80.f);
	logo->setSmooth();
	m_Gui.add(logo);

	// Title
	/*auto title = std::make_shared<tgui::Label>();
	title->setText("Terra");
	title->setTextSize(42);
	title->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(title) / 2, 80.f);
	title->setTextColor(sf::Color::White);
	m_Gui.add(title, "title");*/

	// Startbutton
	tgui::Button::Ptr button = theme->load("Button"); // Verwenden von Theme für Button
	button->setText("--- Start Game ---");
	button->setTextSize(28);
	button->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(button) / 2, 200.f);
	button->connect("clicked", []() { Game::m_pEngine->ChangeState(new GameStatePlay()); });
	m_Gui.add(button, "button");

    InputManager::GetInstance().RegisterEventObserver(this);

	// Finish initialization
	m_bIsInitialized = true;
}

void GameStateIntro::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// Manager updates
	InputManager::GetInstance().Update(pWindow, &m_Gui);

	// Drawing
	m_Gui.draw();
}

void GameStateIntro::OnInputUpdate(std::string strEvent)
{
    std::size_t iDelimiterPos = strEvent.find('_');
	if (iDelimiterPos == std::string::npos)
	{
		return;
	}
	std::string strKey = strEvent.substr(1, iDelimiterPos-1);
    std::string strState = strEvent.substr(iDelimiterPos+1, 1);
    
    if(strState == "P" && strKey == "FIRE" && !m_bKeyPressed)
    {
        // Prevent of double changing states.
        m_bKeyPressed = true;
		Game::m_pEngine->ChangeState(new GameStatePlay());
    }
}