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

	const float degree_to_rad = ((M_PI) / 180.f);
	float shrink_factor_a = fabs(sin(pPositionComponent->GetRotation() * degree_to_rad));
	float shrink_factor_b = fabs(sin(pPositionOtherComponent->GetRotation() * degree_to_rad));

	sf::Vector2f pos_a = pPositionComponent->GetPosition();
	sf::Vector2f size_a = sf::Vector2f(m_fWidth, m_fHeight);
	sf::Vector2f pos_b = pPositionOtherComponent->GetPosition();
	sf::Vector2f size_b = sf::Vector2f(pOther->m_fWidth, pOther->m_fHeight);

	pos_a.x -= (size_a.x / 4.f) * shrink_factor_a + (size_a.x / 2.f);
	pos_a.y += (size_a.y / 4.f) * shrink_factor_a - (size_a.y / 2.f);
	size_a.x += (size_a.x / 2.f) * shrink_factor_a;
	size_a.y -= (size_a.y / 2.f) * shrink_factor_a;
	m_CollisionBox = sf::FloatRect(pos_a, size_a);

	pos_b.x -= (size_b.x / 4.f) * shrink_factor_b + (size_b.x / 2.f);
	pos_b.y += (size_b.y / 4.f) * shrink_factor_b - (size_b.y / 2.f);
	size_b.x += (size_b.x / 2.f) * shrink_factor_b;
	size_b.y -= (size_b.y / 2.f) * shrink_factor_b;
	pOther->m_CollisionBox = sf::FloatRect(pos_b, size_b);
    
    sf::Vector2f n = pos_b - pos_a;		// Vector from A to B
    float a_extent = size_a.x * 0.5f;			    // Calculate half extents along x axis
    float b_extent = size_b.x * 0.5f;
    float x_overlap = a_extent + b_extent - fabs(n.x);		// Calculate overlap on x axis
    // SAT test on x axis
    if (x_overlap > 0)
    {
        float a_extent = size_a.y * 0.5f;		// Calculate half extents along y axis
        float b_extent = size_b.y * 0.5f;
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
	/*
    sf::RectangleShape test(sf::Vector2f(m_CollisionBox.width, m_CollisionBox.height));
    if (m_bHit) test.setFillColor(sf::Color::Magenta);
    else test.setFillColor(sf::Color::Blue);
    test.setPosition(sf::Vector2f(m_CollisionBox.left, m_CollisionBox.top));

    pWindow->draw(test);
	*/
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
