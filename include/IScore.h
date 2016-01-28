/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IComponent.h"
#include "eventbus\EventBus.hpp"
#include "ScoreEvent.h"
#include "SoundManager.h"

class IScore : public IComponent
{
public:
    IScore() : m_iScore(0) { }
    virtual ~IScore() { }
    virtual void AddScore(int iScore)
	{
		m_iScore += iScore;
		if (GetAssignedGameObject() != nullptr && GetAssignedGameObject()->GetID().compare("ship") == 0)
		{
			EventBus::FireEvent(ScoreEvent(this, iScore, GetAssignedGameObject(), nullptr));
			SoundManager::GetInstance().PlaySoundScore();
		}
	}
    virtual void SetScore(int iScore)
	{
		if (GetAssignedGameObject() != nullptr && GetAssignedGameObject()->GetID().compare("ship") == 0)
		{
			EventBus::FireEvent(ScoreEvent(this, iScore - m_iScore, GetAssignedGameObject(), nullptr));
		}
		m_iScore = iScore;
	}
    virtual int GetScore() { return m_iScore; }
    virtual int GetScoreLimit() { return std::numeric_limits<int>::max() - 1; }
    virtual void Serialize(SerializeNode* pParentNode)
    {
        pParentNode->AddElement(new SerializeNode("Score", ESerializeNodeType::Property, std::to_string(m_iScore)));
    }
    static void Deserialize(SerializeNode* pNode, IScore* pParentComponent)
    {
        int iScore = stoi((pNode->GetNode("Score"))->GetValue());
        pParentComponent->m_iScore = iScore;
    }
    EComponentType GetComponentType()
    {
        return EComponentType::Score;
    }
    virtual std::string GetComponentName() { return std::string("IScore"); }
protected:
    int m_iScore;
};