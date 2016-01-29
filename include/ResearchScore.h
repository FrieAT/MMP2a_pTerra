/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IScore.h"
#include "IFrameObserver.h"

class ResearchScore : public IScore
{
public:
    ResearchScore(int iLevelLimit, int iLevelUpCostFactor);
    ~ResearchScore();
    void AddScore(int iScore);
    void SetScore(int iScore);
    void Serialize(SerializeNode* pParentNode);
    int GetScoreLimit();
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("ResearchScore"); }
protected:
    int m_iLevelLimit;
    int m_iLevelUpCostFactor;
    int m_iCurrentLevel;
	bool m_bTerraCreated = false;
};