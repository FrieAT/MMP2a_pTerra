/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <math.h>

#include "Game.h"
#include "IPosition.h"
#include "IMovement.h"
#include "DynamicView.h"
#include "FrameManager.h"

DynamicView::DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector)
{    
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = MoveVector;
	m_zoom = 1.f;
}

DynamicView::~DynamicView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void DynamicView::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
}

sf::FloatRect DynamicView::GetViewport()
{
    return m_pView.getViewport();
}

void DynamicView::OnFrameUpdate(sf::Time DeltaTime)
{

}

void DynamicView::OnFrameDraw(sf::RenderWindow* pWindow)
{
    m_pView = pWindow->getView();
    m_pView.setCenter(0, 0);
    
    // Set camera to center of screen
    IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    if (pPositionComponent != nullptr)
    {
        sf::Vector2f CurrentPos = pPositionComponent->GetPosition();
        sf::Vector2f CenterScreen(Game::m_iWindowWidth / 2.f, Game::m_iWindowHeight / 2.f);
        m_pView.move(CurrentPos.x - CenterScreen.x, CurrentPos.y - CenterScreen.y);
    }
    
    // Set zoom based on player ship speed
    IMovement* pMovementComponent = static_cast<IMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
    sf::Vector2f moveVector = pMovementComponent->GetVelocity();
    
    if (moveVector.x != 0 || moveVector.y != 0)
    {
        m_zoom = 1.0f / (sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y) / 200);
    }
    else
    {
        m_zoom = 1.0f;
    }
    
    // Clamp value
    m_zoom = m_zoom >= 1.0f ? 1.0f
    : m_zoom <= 0.5f ? 0.5f
    : m_zoom;
    
	// m_pView->setSize(sf::Vector2f(pWindow->getSize()) / m_zoom);
    pWindow->setView(m_pView);
}

void DynamicView::Serialize(SerializeNode *pParentNode)
{
    IView::Serialize(pParentNode);
}

IComponent* DynamicView::Deserialize(SerializeNode *pNode)
{
    DynamicView* pComponent = new DynamicView(sf::FloatRect(), sf::Vector2f());
    
    IView::Deserialize(pNode, pComponent);
    
    return pComponent;
}