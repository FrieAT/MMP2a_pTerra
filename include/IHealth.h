/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ObjectManager.h"
#include "IEngine.h"
#include "eventbus\EventBus.hpp"
#include "PlayerShieldRegenerationEvent.h"

class IHealth : public IComponent
{
public:
    IHealth() : m_fHealth(0.f), m_fShield(0.f), m_bShieldActive(false)
    {
        m_pShieldAsset = new GameObject("effect");
        m_pShieldAsset->SetTemporaryState(true);
        m_pShieldAsset->SetAssistedState(true);
        m_pShieldAsset->SetComponent(new PixelPosition(sf::Vector2f(), sf::Vector2f(44.375f, 75.f)));
    }
    virtual ~IHealth()
    {
        m_pShieldAsset->SetAssistedState(false);
        ObjectManager::GetInstance().RemoveGameObject(m_pShieldAsset);
    }
    virtual void Init()
    {
       // Huh, what am I doing here?
    }
	EComponentType GetComponentType()
	{
		return EComponentType::Health;
	}
    virtual float GetHealth() { return m_fHealth; }
    virtual float GetShield() { return m_fShield; }
	virtual void Damage(float fDamage)
    {
        if(m_fShield > 0.f)
        {
            m_fShield -= fDamage;
            if(m_fShield < 0.f)
            {
                fDamage = m_fShield * -1;
                m_fShield = 0.f;
            }
            else
            {
                fDamage = 0.f;
            }
        }
        m_fHealth -= fDamage;
        
        // NOTE: Anything else what should be done shall Child-Class decide.
    }
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        pParentNode->AddElement(new SerializeNode("Health", ESerializeNodeType::Property, std::to_string(m_fHealth)));
        pParentNode->AddElement(new SerializeNode("Shield", ESerializeNodeType::Property, std::to_string(m_fShield)));
        pParentNode->AddElement(new SerializeNode("ShieldActive", ESerializeNodeType::Property, std::to_string(m_bShieldActive)));
    }
    static void Deserialize(SerializeNode* pNode, IHealth* pParentComponent)
    {
        float fHealth = stof((pNode->GetNode("Health"))->GetValue());
        pParentComponent->m_fHealth = fHealth;
        
        float fShield = stof((pNode->GetNode("Shield"))->GetValue());
        pParentComponent->m_fShield = fShield;
        
        int iShieldActive = stoi((pNode->GetNode("ShieldActive"))->GetValue());
        pParentComponent->m_bShieldActive = (iShieldActive ? true : false);
        
        pParentComponent->DrawShield(pParentComponent->m_bShieldActive, true);
    }
    virtual std::string GetComponentName() { return std::string("IHealth"); }
protected:
    float m_fHealth;
    float m_fShield;
    bool m_bShieldActive;
    GameObject* m_pShieldAsset;
    virtual void RegenerateShield(sf::Time DeltaTime)
    {
        IPosition* pPositionObject = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
        if(pPositionObject != nullptr)
        {
            IPosition* pPositionShield = static_cast<IPosition*>(m_pShieldAsset->GetComponent(EComponentType::Position));
            pPositionShield->SetPosition(pPositionObject->GetPosition());
            pPositionShield->SetRotation(pPositionObject->GetRotation());
        }
        
		IEngine* pEngine = static_cast<IEngine*>(GetAssignedGameObject()->GetComponent(EComponentType::Engine));
		if (pEngine != nullptr)
		{
			if (m_fShield < 100.f)
			{
				// Only recharge shield when Energy is over 80%
				if ((pEngine->GetFuel() / pEngine->GetMaxFuel()) >= 0.8f)
				{
					m_fShield += 5.f * DeltaTime.asSeconds();
					if (m_fShield > 100.f)
					{
						m_fShield = 100.f;
					}
					EventBus::FireEvent(PlayerShieldRegenerationEvent(this, GetAssignedGameObject(), m_fShield));
				}

				if (m_fShield <= 0.f)
				{
					DrawShield(false);
				}
				else
				{
					DrawShield(true);

					IDrawing* pShieldDrawing = static_cast<IDrawing*>(m_pShieldAsset->GetComponent(EComponentType::Drawing));
					if (pShieldDrawing != nullptr)
					{
						pShieldDrawing->SetColor(sf::Color(255, 255, 255, static_cast<int>(255 * (m_fShield / 100.f))));
					}
				}
			}
			else
			{
				DrawShield(true);
				m_fShield = 100.f;
			}
		}
    }
    void DrawShield(bool bQuestion, bool bForce = false)
    {
        if(bForce || (!bForce && bQuestion != m_bShieldActive))
        {
            m_bShieldActive = bQuestion;
            if(m_bShieldActive)
            {
                SpriteDrawing* pSpriteComponent = new SpriteDrawing("assets/lilee/shield_player_fixed.png");
                pSpriteComponent->GenerateTextureAreas(4, 1);
                pSpriteComponent->SetUpdateFrameRate(20);
                m_pShieldAsset->SetComponent(pSpriteComponent);
            }
            else
            {
                m_pShieldAsset->RemoveComponent(EComponentType::Drawing);
            }
        }
    }
};