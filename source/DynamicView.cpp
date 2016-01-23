/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "Game.h"
#include "IPosition.h"
#include "IMovement.h"
#include "DynamicView.h"
#include "FrameManager.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ObjectManager.h"

DynamicView::DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector)
{
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = MoveVector;
    m_zoom = 1.f;
    m_pView = new sf::View(ViewSize);

	m_pVignett = new GameObject("screen");
	m_pVignett->SetTemporaryState(true);
	m_pVignett->SetAssistedState(true);
	m_pVignett->SetComponent(new PixelPosition(sf::Vector2f(), sf::Vector2f(Game::m_iWindowWidth / 2.f, Game::m_iWindowHeight / 2.f)));
	m_pVignett->SetComponent(new SpriteDrawing("assets/lilee/FG_vignette.png", sf::Vector2f(Game::m_iWindowWidth, Game::m_iWindowHeight)));
}

DynamicView::~DynamicView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    delete m_pView;
	m_pVignett->SetAssistedState(true);
	ObjectManager::GetInstance().RemoveGameObject(m_pVignett);
}

void DynamicView::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
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
		
		IPosition* pVignettPosition = static_cast<IPosition*>(m_pVignett->GetComponent(EComponentType::Position));
		if (pVignettPosition != nullptr)
		{
            // sf::Vector2f CurrentSize = m_pView->getSize();
            // pVignettPosition->SetOrigin(sf::Vector2f(CurrentSize.x / 2.f, CurrentSize.y / 2.f));
			pVignettPosition->SetPosition(pPositionComponent->GetPosition());
		}
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
}

void DynamicView::OnFrameDraw(sf::RenderWindow* pWindow)
{
	sf::Vector2f NewSize(sf::Vector2f(pWindow->getSize()) / m_zoom);

	IDrawing* pVignettDrawing = static_cast<IDrawing*>(m_pVignett->GetComponent(EComponentType::Drawing));
	if (pVignettDrawing != nullptr)
	{
		pVignettDrawing->SetScale(NewSize * 1.25f);
	}

    m_pView->setSize(NewSize);
    pWindow->setView(*m_pView);
}

void DynamicView::Serialize(SerializeNode *pParentNode)
{
    IView::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ViewSizeX", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).left)));
    pParentNode->AddElement(new SerializeNode("ViewSizeY", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).top)));
    pParentNode->AddElement(new SerializeNode("ViewSizeWidth", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).width)));
    pParentNode->AddElement(new SerializeNode("ViewSizeHeight", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).height)));
    pParentNode->AddElement(new SerializeNode("MoveVectorX", ESerializeNodeType::Property, std::to_string(m_MoveVector.x)));
    pParentNode->AddElement(new SerializeNode("MoveVectorY", ESerializeNodeType::Property, std::to_string(m_MoveVector.y)));
}

IComponent* DynamicView::Deserialize(SerializeNode *pNode)
{
    DynamicView* pComponent = new DynamicView(sf::FloatRect(), sf::Vector2f());
    
    IView::Deserialize(pNode, pComponent);
    
    sf::FloatRect ViewSize;
    ViewSize.left = stof((pNode->GetNode("ViewSizeX"))->GetValue());
    ViewSize.top = stof((pNode->GetNode("ViewSizeY"))->GetValue());
    ViewSize.width = stof((pNode->GetNode("ViewSizeWidth"))->GetValue());
    ViewSize.height = stof((pNode->GetNode("ViewSizeHeight"))->GetValue());
    pComponent->m_pView = new sf::View(ViewSize);
    
    sf::Vector2f MoveVector;
    MoveVector.x = stof((pNode->GetNode("MoveVectorX"))->GetValue());
    MoveVector.y = stof((pNode->GetNode("MoveVectorY"))->GetValue());
    pComponent->m_MoveVector = MoveVector;
    
    return pComponent;
}