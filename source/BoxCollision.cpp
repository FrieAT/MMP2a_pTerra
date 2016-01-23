/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "BoxCollision.h"
#include "CollisionManager.h"

BoxCollision::BoxCollision(float fWidth, float fHeight)
: m_fWidth(fWidth)
, m_fHeight(fHeight)
, m_bHit(false)
{
    
}

BoxCollision::~BoxCollision()
{
    CollisionManager::GetInstance().UnregisterCollisionbody(this);
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void BoxCollision::Init()
{
    CollisionManager::GetInstance().RegisterCollisionbody(this);
    FrameManager::GetInstance().RegisterEventObserver(this);
}

bool BoxCollision::colliding(ICollision* pCollisionBody)
{
    BoxCollision* pOther = static_cast<BoxCollision*> (pCollisionBody);
    IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    IPosition* pPositionOtherComponent = static_cast<IPosition*>(pCollisionBody->GetAssignedGameObject()->GetComponent(EComponentType::Position));
    
    if(pPositionComponent == nullptr || pPositionOtherComponent == nullptr)
    {
        m_bHit = false;
        return false;
    }
    
    sf::FloatRect a = sf::FloatRect(pPositionComponent->GetPosition(),sf::Vector2f(m_fWidth,m_fHeight));
    sf::FloatRect b = sf::FloatRect();
    
    auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
    {
        return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
    };
    
    sf::Vector2f n = pPositionOtherComponent->GetPosition() - pPositionComponent->GetPosition();		// Vector from A to B
    float a_extent = m_fWidth * 0.5f;			    // Calculate half extents along x axis
    float b_extent = pOther->m_fWidth * 0.5f;
    float x_overlap = a_extent + b_extent - fabs(n.x);		// Calculate overlap on x axis
    // SAT test on x axis
    if (x_overlap > 0)
    {
        float a_extent = m_fHeight * 0.5f;		// Calculate half extents along y axis
        float b_extent = pOther->m_fHeight * 0.5f;
        float y_overlap = a_extent + b_extent - fabs(n.y);	// Calculate overlap on y axis
        
        CollisionEvent col_ev;
        col_ev.Body1 = this->GetAssignedGameObject();
        col_ev.Body2 = pOther->GetAssignedGameObject();
        
        if (y_overlap > 0)
        {
            // Find out which axis is axis of least penetration
            if (x_overlap < y_overlap)
            {
                // Point towards B knowing that n points from A to B
                if (n.x < 0)
                {
                    col_ev.normal = sf::Vector2f(1.0f, 0.0f);
                }
                else
                {
                    col_ev.normal = sf::Vector2f(-1.0f, 0.0f);
                }
                CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
                
                m_bHit = true;
                return true;
            }
            else
            {
                // Point towards B knowing that n points from A to B
                if (n.y < 0)
                {
                    col_ev.normal = sf::Vector2f(0, 1);
                }
                else
                {
                    col_ev.normal = sf::Vector2f(0, -1);
                }
                CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
                m_bHit = true;
                return true;
            }
        }
    }
    m_bHit = false;
    return false;
}

void BoxCollision::OnFrameDraw(sf::RenderWindow* pWindow)
{
    IPosition* pos = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    sf::RectangleShape test(sf::Vector2f(m_fWidth,m_fHeight));
    if (m_bHit) test.setFillColor(sf::Color::Magenta);
    else test.setFillColor(sf::Color::Blue);
    test.setPosition(pos->GetPosition() - sf::Vector2f(m_fWidth/2, m_fHeight/2));

    // pWindow->draw(test);
}

void BoxCollision::Serialize(SerializeNode *pParentNode)
{
    this->ICollision::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("Width", ESerializeNodeType::Property, std::to_string(m_fWidth)));
    pParentNode->AddElement(new SerializeNode("Height", ESerializeNodeType::Property, std::to_string(m_fHeight)));
    pParentNode->AddElement(new SerializeNode("Hit", ESerializeNodeType::Property, std::to_string(m_bHit)));
}

IComponent* BoxCollision::Deserialize(SerializeNode* pNode)
{
    float fWidth = stof((pNode->GetNode("Width"))->GetValue());
    float fHeight = stof((pNode->GetNode("Height"))->GetValue());
    int iHit = stoi((pNode->GetNode("Hit"))->GetValue());
    
    BoxCollision* pComponent = new BoxCollision(fWidth, fHeight);
    pComponent->m_bHit = (iHit ? true : false);
    
    return pComponent;
}
