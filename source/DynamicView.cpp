/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <math.h>

#include "Game.h"
#include "IPosition.h"
#include "IMovement.h"
#include "DynamicView.h"
#include "FrameManager.h"

DynamicView::DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector, float fSpeed)
{    
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = MoveVector;
	m_fSpeed = fSpeed;
	m_zoom = 1.f;
	m_pView = new sf::View(ViewSize);
    
    FrameManager::GetInstance().RegisterEventObserver(this);
}

DynamicView::~DynamicView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    
    delete m_pView;
}

sf::FloatRect DynamicView::GetViewport()
{
    return m_pView->getViewport();
}

void DynamicView::OnFrameUpdate(sf::Time DeltaTime)
{
	// Set camera to center of screen
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (pPositionComponent != nullptr)
	{
		m_pView->setCenter(pPositionComponent->GetCenter());
	}

	// Set zoom based on player ship speed
	IMovement* pMovementComponent = static_cast<IMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
	sf::Vector2f moveVector = pMovementComponent->GetVelocity();

	m_zoom = 1.0f / (std::sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y) / 200);

	// Clamp value
	m_zoom = m_zoom >= 1.0f ? 1.0f
		: m_zoom <= 0.5f ? 0.5f
		: m_zoom;
}

void DynamicView::OnFrameDraw(sf::RenderWindow* pWindow)
{
	m_pView->setSize(sf::Vector2f(pWindow->getSize()) / m_zoom);
    pWindow->setView(*m_pView);
}