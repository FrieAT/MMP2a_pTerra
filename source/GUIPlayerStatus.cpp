/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include <iomanip>

#include "..\include\GUIPlayerStatus.h"
#include "Game.h"
#include "IScore.h"

GUIPlayerStatus::~GUIPlayerStatus()
{

}

void GUIPlayerStatus::Init()
{
	// Create HealthBar
	m_HealthBar = std::make_shared<tgui::ProgressBar>();
	m_HealthBar->setPosition(80, Game::m_iWindowHeight - (70 * 3));
	m_HealthBar->setFillDirection(tgui::ProgressBar::FillDirection::LeftToRight);
	m_HealthBar->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(800));
	m_HealthBar->setMinimum(0);
	m_HealthBar->setMaximum(100);
	m_HealthBar->setValue(100);
	m_HealthBar->setSize(tgui::Layout2d(170, 35));
	auto HealthBarRenderer = m_HealthBar->getRenderer();
	HealthBarRenderer->setBackgroundColor(sf::Color(255, 255, 255, 40));
	HealthBarRenderer->setForegroundColor(sf::Color(250, 0, 0, 200));
	HealthBarRenderer->setBorders(0, 0);
	m_gui.add(m_HealthBar);

	// Create Health Label
	m_Health = std::make_shared<tgui::Label>();
	m_Health->setTextColor(sf::Color::Red);
	m_Health->setText("100");
	std::cout << m_Health->getFullSize().x << std::endl;
	m_Health->setPosition(24, Game::m_iWindowHeight - (70 * 3) - 4);
	m_gui.add(m_Health);

	// Create ShieldBar
	m_ShieldBar = std::make_shared<tgui::ProgressBar>();
	m_ShieldBar->setPosition(80, Game::m_iWindowHeight - (70 * 2));
	m_ShieldBar->setFillDirection(tgui::ProgressBar::FillDirection::LeftToRight);
	m_ShieldBar->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(800));
	m_ShieldBar->setMinimum(0);
	m_ShieldBar->setMaximum(100);
	m_ShieldBar->setValue(0);
	m_ShieldBar->setSize(tgui::Layout2d(170, 35));
	auto ShieldBarRenderer = m_ShieldBar->getRenderer();
	ShieldBarRenderer->setBackgroundColor(sf::Color(255, 255, 255, 40));
	ShieldBarRenderer->setForegroundColor(sf::Color::Yellow);
	ShieldBarRenderer->setBorders(0, 0);
	m_gui.add(m_ShieldBar);

	// Create ShieldLabel
	m_Shield = std::make_shared<tgui::Label>();
	m_Shield->setTextColor(sf::Color::Yellow);
	m_Shield->setText("100");
	m_Shield->setPosition(24, Game::m_iWindowHeight - (70 * 2) - 4);
	m_gui.add(m_Shield);

	// Create EnergyBar

	// Create EnergyLabel

	// Create ScoreLabel
	m_Score = std::make_shared<tgui::Label>();
	m_Score->setTextColor(sf::Color::White);
	m_Score->setText("Score: 0");
	m_Score->setTextSize(30);
	m_Score->setPosition(Game::m_iWindowWidth - 450, 10);
	m_gui.add(m_Score);
}

void GUIPlayerStatus::onEvent(PlayerDamageEvent* e)
{
	std::stringstream health;
	health << std::fixed << std::setprecision(0) << e->GetHealth();
	m_Health->setText(health.str());
	m_HealthBar->setValue((int)e->GetHealth());

	std::stringstream shield;
	shield << std::fixed << std::setprecision(0) << e->GetShield();
	m_Shield->setText(shield.str());
	m_ShieldBar->setValue((int)e->GetShield());
}

void GUIPlayerStatus::onEvent(PlayerShieldRegenerationEvent* e)
{
	std::stringstream shield;
	shield << std::fixed << std::setprecision(0) << e->GetShield();
	m_Shield->setText(shield.str());
	m_ShieldBar->setValue((int)e->GetShield());
}

void GUIPlayerStatus::onEvent(ScoreEvent* e)
{
	IScore* currentScore = static_cast<IScore*>(e->GetReceiver()->GetComponent(EComponentType::Score));
	std::stringstream score;
	score << std::fixed << std::setprecision(0) << currentScore->GetScore();
	m_Score->setText("Score: " + score.str());
}