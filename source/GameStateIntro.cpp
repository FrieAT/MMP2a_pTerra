/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "GameStateIntro.h"
#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
// #include "WorldManager.h"

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
	background->setSize(static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight));
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

    float fCurrentHeight = 200.f;
    
	// Startbutton
	tgui::Button::Ptr buttonStart = theme->load("Button"); // Verwenden von Theme für Button
	if (Game::m_pEngine->IsInitialized(EGameState::GameStatePlay))
	{
		buttonStart->setText("Continue Game");
		buttonStart->connect("clicked", []() {
			Game::m_pEngine->ChangeState(EGameState::GameStatePlay);
		});
	}
	else
	{
		buttonStart->setText("New Game");
		buttonStart->connect("clicked", []() {
			Game::m_pEngine->ChangeState(EGameState::GameStatePlay);
		});
	}
	buttonStart->setTextSize(28);
	buttonStart->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonStart) / 2, fCurrentHeight);
	m_Gui.add(buttonStart, "buttonStart");
    fCurrentHeight += 200.f;

    // Load Last SaveGame, but only show if a savegame exists.
    std::ifstream ifile("savegame.txt");
    if(ifile && !Game::m_pEngine->IsInitialized(EGameState::GameStatePlay))
    {
        tgui::Button::Ptr buttonLoad = theme->load("Button"); // Verwenden von Theme für Button
        buttonLoad->setText("Load Last Game");
        buttonLoad->connect("clicked", []() {
            Game::m_pEngine->ChangeState(EGameState::GameStatePlay);
            GameStatePlay* pNewState = static_cast<GameStatePlay*>(Game::m_pEngine->GetLastState());
            pNewState->SetLoadGame("savegame.txt");
        });
        buttonLoad->setTextSize(28);
        buttonLoad->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonLoad) / 2, fCurrentHeight);
        m_Gui.add(buttonLoad, "buttonLoad");
        fCurrentHeight += 200.f;
    }
    
	// Exit button
	tgui::Button::Ptr buttonExit = theme->load("Button"); // Verwenden von Theme für Button
	buttonExit->setText("Exit");
	buttonExit->connect("clicked", [this]() {
		m_bExit = true;
	});
	buttonExit->setTextSize(28);
	buttonExit->setPosition(Game::m_iWindowWidth / 2 - tgui::bindWidth(buttonExit) / 2, fCurrentHeight);
	m_Gui.add(buttonExit, "buttonExit");
    fCurrentHeight += 200.f;

    //InputManager::GetInstance().RegisterEventObserver(this);
}

void GameStateIntro::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// Check for exit
	if (m_bExit)
	{
		pWindow->close();
	}

	// Manager updates
	//InputManager::GetInstance().Update(pWindow, &m_Gui);

	// No managers, give Events directly to Gui
	sf::Event Event;
	while (pWindow->pollEvent(Event))
	{
		m_Gui.handleEvent(Event);
	}

	// Drawing
	m_Gui.draw();
}

void GameStateIntro::OnInputUpdate(std::string strEvent)
{
    /*std::size_t iDelimiterPos = strEvent.find('_');
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
    }*/
}