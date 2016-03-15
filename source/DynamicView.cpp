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

#define _USE_MATH_DEFINES
#include <math.h>

DynamicView::DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector)
{
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = MoveVector;
    m_zoom = 1.f;
	m_ViewSize = ViewSize;
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
	return m_ViewSize;
}

void DynamicView::OnFrameDraw(sf::RenderWindow* pWindow)
{
	sf::View view(m_ViewSize);

	// Set camera to center of screen
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (pPositionComponent != nullptr)
	{
		view.setCenter(pPositionComponent->GetCenter());
		if (Game::m_pEngine->m_bRotateCamera)
		{
			view.setRotation(pPositionComponent->GetRotation());
		}
	}

	// Set zoom based on player ship speed
	IMovement* pMovementComponent = static_cast<IMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
	sf::Vector2f moveVector = pMovementComponent->GetVelocity();

	if (moveVector.x != 0 || moveVector.y != 0)
	{
		m_zoom = 0.95f - (sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y) / 1200);
	}
	else
	{
		m_zoom = 0.95f;
	}

	// Clamp value
	m_zoom = m_zoom >= 0.95f ? 0.95f
		: m_zoom <= 0.58f ? 0.58f
		: m_zoom;

	sf::Vector2f NewSize(sf::Vector2f(pWindow->getSize()) / m_zoom);

	view.setSize(NewSize);

	// Add screen shake
	if (m_ScreenShake != sf::Vector2f(0.f, 0.f))
	{
		view.move(m_ScreenShake);
		m_ScreenShake = m_ScreenShake / 1.05f;

		if (sqrt(m_ScreenShake.x * m_ScreenShake.x + m_ScreenShake.y * m_ScreenShake.y) < 0.01f)
		{
			m_ScreenShake = sf::Vector2f(0.f, 0.f);
		}
		else
		{
			// Randomly rotate vector
			float radians = (rand() % 360) / 180 * M_PI;
			m_ScreenShake.x = m_ScreenShake.x * cos(radians) - m_ScreenShake.y * sin(radians);
			m_ScreenShake.y = m_ScreenShake.x * sin(radians) - m_ScreenShake.y * cos(radians);
		}
	}

	Game::m_pEngine->SetView(view); // pWindow->setView(m_pView);
}

void DynamicView::onEvent(PlayerDamageEvent* e)
{
	float currentShakeLength = sqrt(m_ScreenShake.x * m_ScreenShake.x + m_ScreenShake.y * m_ScreenShake.y);
	
	sf::Vector2f shakeDirection;
	if (currentShakeLength == 0.f)
	{
		// Use random shake direction
		float randVal = (rand() % 100) / 100.f;
		shakeDirection = sf::Vector2f(randVal, 1 - randVal);
	}
	else
	{
		shakeDirection = sf::Vector2f(m_ScreenShake.x / currentShakeLength, m_ScreenShake.y / currentShakeLength);
	}

	// Add damage received to shake length
	currentShakeLength += e->GetDamage();

	// Calculate new shake vector
	m_ScreenShake = shakeDirection * currentShakeLength;
}

void DynamicView::Serialize(SerializeNode *pParentNode)
{
    IView::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ViewSizeX", ESerializeNodeType::Property, std::to_string(m_ViewSize.left)));
    pParentNode->AddElement(new SerializeNode("ViewSizeY", ESerializeNodeType::Property, std::to_string(m_ViewSize.top)));
    pParentNode->AddElement(new SerializeNode("ViewSizeWidth", ESerializeNodeType::Property, std::to_string(m_ViewSize.width)));
    pParentNode->AddElement(new SerializeNode("ViewSizeHeight", ESerializeNodeType::Property, std::to_string(m_ViewSize.height)));
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
    pComponent->m_ViewSize = ViewSize;
    
    sf::Vector2f MoveVector;
    MoveVector.x = stof((pNode->GetNode("MoveVectorX"))->GetValue());
    MoveVector.y = stof((pNode->GetNode("MoveVectorY"))->GetValue());
    pComponent->m_MoveVector = MoveVector;
    
    return pComponent;
}