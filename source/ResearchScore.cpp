/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "ResearchScore.h"
#include "IPosition.h"
#include "INavigation.h"
#include "WorldManager.h"
#include "GameObjectFactory.h"

ResearchScore::ResearchScore(int iLevelLimit, int iLevelUpCostFactor)
: IScore()
, m_iLevelLimit(iLevelLimit)
, m_iLevelUpCostFactor(iLevelUpCostFactor)
, m_iCurrentLevel(0)
{
    
}

ResearchScore::~ResearchScore()
{
    
}

void ResearchScore::AddScore(int iScore)
{
    IScore::AddScore(iScore);
    
    int iNextLevelScore = (m_iCurrentLevel + 1) * m_iLevelUpCostFactor;
    
    if(m_iScore >= iNextLevelScore && GetAssignedGameObject() != nullptr)
    {
        m_iCurrentLevel++;
    
        // Check if game object has a INavigation and set a new waypoint to next planet if it isn´t active.
        INavigation* pNavigationComponent = static_cast<INavigation*>(GetAssignedGameObject()->GetComponent(EComponentType::Navigation));
        IPosition* pPositionOwner = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
        if(pPositionOwner != nullptr && pNavigationComponent != nullptr && GetScore() >= GetScoreLimit())
        {
            // Get the holy Position of Terra
            sf::Vector2f NextCoords = WorldManager::GetInstance().GetNextNearestObjectPos(pPositionOwner->GetPosition(), EWorldObjectType::Terra);
            
            // Generate Terra
            GameObjectFactory::CreatePlanet(NextCoords, EWorldObjectType::Terra);
            
            // Set Navigation to Terra.
            pNavigationComponent->SetNavigationPoint(NextCoords);
            pNavigationComponent->SetNavigationActive(true);
        }
        else if(pPositionOwner != nullptr && pNavigationComponent != nullptr && !pNavigationComponent->IsNavigationActive())
        {
            EWorldObjectType SearchObject = EWorldObjectType::Planet;
			/*
            if(rand() % 100 <= 50)
            {
                SearchObject = EWorldObjectType::Planet;
            }
			*/
            
            sf::Vector2f NextCoords = WorldManager::GetInstance().GetNextNearestObjectPos(pPositionOwner->GetPosition(), SearchObject);
            pNavigationComponent->SetNavigationPoint(NextCoords);
            pNavigationComponent->SetNavigationActive(true);
        }
    }
}

void ResearchScore::SetScore(int iScore)
{
    IScore::SetScore(iScore);
    AddScore(0);
}

int ResearchScore::GetScoreLimit()
{
    return (m_iLevelLimit * m_iLevelUpCostFactor);
}

void ResearchScore::Serialize(SerializeNode *pParentNode)
{
    IScore::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("LevelLimit", ESerializeNodeType::Property, std::to_string(m_iLevelLimit)));
    pParentNode->AddElement(new SerializeNode("LevelUpCostFactor", ESerializeNodeType::Property, std::to_string(m_iLevelUpCostFactor)));
    pParentNode->AddElement(new SerializeNode("CurrentLevel", ESerializeNodeType::Property, std::to_string(m_iCurrentLevel)));
}

IComponent* ResearchScore::Deserialize(SerializeNode *pNode)
{
    ResearchScore* pComponent = new ResearchScore(0, 0);
    
    IScore::Deserialize(pNode, pComponent);
    
    int iLevelLimit = stoi((pNode->GetNode("LevelLimit"))->GetValue());
    pComponent->m_iLevelLimit = iLevelLimit;
    
    int iLevelUpCostFactor = stoi((pNode->GetNode("LevelUpCostFactor"))->GetValue());
    pComponent->m_iLevelUpCostFactor = iLevelUpCostFactor;
    
    int iCurrentLevel = stoi((pNode->GetNode("CurrentLevel"))->GetValue());
    pComponent->m_iCurrentLevel = iCurrentLevel;
    
    return pComponent;
}