/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <math.h>

#include "Game.h"
#include "IPosition.h"
#include "ScriptedView.h"
#include "FrameManager.h"

ScriptedView::ScriptedView(sf::FloatRect ViewSize, sf::Vector2f MoveVector, float fSpeed)
{
    float fStep = (fSpeed / sqrt(pow(MoveVector.x,2.0f) + pow(MoveVector.y,2.0f)));
    
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = MoveVector;
    m_fSteps = fStep;
    m_fSpeed = fSpeed;
    
    m_pView = new sf::View(ViewSize);
    
    FrameManager::GetInstance().RegisterEventObserver(this);
}

ScriptedView::~ScriptedView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    
    delete m_pView;
}

sf::FloatRect ScriptedView::GetViewport()
{
    return m_pView->getViewport();
}

void ScriptedView::OnFrameUpdate(sf::Time DeltaTime)
{
	if (m_CurrentMovePosition.x < m_MoveVector.x || m_CurrentMovePosition.y < m_MoveVector.y)
	{
		// TODO: Maybe repeating?
		float fStepsWithDeltaTime = m_fSteps * DeltaTime.asSeconds();
		sf::Vector2f move = m_MoveVector * fStepsWithDeltaTime;
		m_CurrentMovePosition += move;
		m_pView->move(move);
	}

	// Check if position from current game object is within Boundary
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::Vector2f Position = pPositionComponent->GetPosition();
	sf::Vector2f ViewCenter = m_pView->getCenter();
	sf::Vector2f TopLeftBoundary(ViewCenter.x - Game::m_iWindowWidth * 0.5f, ViewCenter.y - Game::m_iWindowHeight * 0.5f);
	bool bPositionChanged = false;

	// Boundary correction in x-axis
	if (Position.x < TopLeftBoundary.x)
	{
		Position.x = TopLeftBoundary.x;
	}
	else if (Position.x > TopLeftBoundary.x + Game::m_iWindowWidth)
	{
		Position.x = TopLeftBoundary.x + Game::m_iWindowWidth;
	}

	// Boundary correction in y-axis
	if (Position.y < TopLeftBoundary.y)
	{
		Position.y = TopLeftBoundary.y;
	}
	else if (Position.y > TopLeftBoundary.y + Game::m_iWindowHeight)
	{
		Position.y = TopLeftBoundary.y + Game::m_iWindowHeight;
	}

	// Set new position
	pPositionComponent->SetPosition(Position);
}

void ScriptedView::OnFrameDraw(sf::RenderWindow* pWindow)
{
    pWindow->setView(*m_pView);
}