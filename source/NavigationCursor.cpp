/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "NavigationCursor.h"
#include "FrameManager.h"
#include "ObjectManager.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"

NavigationCursor::NavigationCursor()
: INavigation()
{
    m_pCursor = new GameObject("effect");
    m_pCursor->SetTemporaryState(true);
    m_pCursor->SetComponent(new PixelPosition(sf::Vector2f(), sf::Vector2f(8.f, 8.f)));
}

NavigationCursor::~NavigationCursor()
{
    ObjectManager::GetInstance().RemoveGameObject(m_pCursor);
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void NavigationCursor::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
}

void NavigationCursor::SetNavigationPoint(sf::Vector2f PointPosition)
{
    m_NavigationPoint = PointPosition;
}

sf::Vector2f NavigationCursor::GetNavigationPoint()
{
    return m_NavigationPoint;
}

void NavigationCursor::SetNavigationActive(bool bActive, bool bForce)
{
    if(bForce || (!bForce && bActive != m_bActive))
    {
        if(bActive)
        {
            m_pCursor->SetComponent(new SpriteDrawing("assets/cursor.png"));
        }
        else
        {
            m_pCursor->RemoveComponent(EComponentType::Drawing);
        }
    }
    m_bActive = bActive;
}

void NavigationCursor::OnFrameUpdate(sf::Time DeltaTime)
{
    // Ignore Update, if it isn´t active.
    if(!m_bActive)
    {
        return;
    }
    
    IPosition* pObjectPosComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    IPosition* pCursorPosComponent = static_cast<IPosition*>(m_pCursor->GetComponent(EComponentType::Position));
    sf::Vector2f Difference = m_NavigationPoint - pObjectPosComponent->GetPosition();
    float fLength = sqrt((Difference.x * Difference.x) + (Difference.y * Difference.y));
    sf::Vector2f DifferenceNormalized = Difference / fLength;
    float fAngleDegrees = atan2f(Difference.y, Difference.x) * 180.f / M_PI;
    fAngleDegrees -= 275.f;
    while(fAngleDegrees < 0)
    {
        fAngleDegrees += 360.f;
    }
    std::cout << "NavigationRadius: " << m_NavigationPoint.x << " / " << m_NavigationPoint.y << std::endl;
    IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    if(pPositionComponent != nullptr)
    {
        pCursorPosComponent->SetRotation(fAngleDegrees);
        pCursorPosComponent->SetPosition(pPositionComponent->GetPosition() + DifferenceNormalized * 100.f);
        m_fDistance = fLength;
    }
    
    // Wenn das Ziel erreicht worden ist, so deaktiviere wieder die Navigation.
    if(fLength < 100.f)
    {
        // TODO: Mögliche GUI Ausgabe für Ziel erreicht.
        SetNavigationActive(false);
    }
}

void NavigationCursor::OnFrameDraw(sf::RenderWindow *pWindow)
{
    
}

IComponent* NavigationCursor::Deserialize(SerializeNode *pNode)
{
    NavigationCursor* pComponent = new NavigationCursor();
    
    INavigation::Deserialize(pNode, pComponent);
    
    if(pComponent->m_bActive)
    {
        pComponent->SetNavigationActive(pComponent->m_bActive, true);
    }
    return pComponent;
}
