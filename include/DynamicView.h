/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IView.h"
#include "IFrameObserver.h"
#include "eventbus/EventHandler.hpp"
#include "PlayerDamageEvent.h"

class DynamicView : public IView, public IFrameObserver, public EventHandler<PlayerDamageEvent>
{
public:
    DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector);
    ~DynamicView();
    void Init() override;
    void OnFrameDraw(sf::RenderWindow* pWindow) override;
	void onEvent(PlayerDamageEvent* e) override;
    void Serialize(SerializeNode* pParentNode) override;
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() override { return std::string("DynamicView"); }
    sf::FloatRect GetViewport() override;
private:
	sf::FloatRect m_ViewSize;
    sf::Vector2f m_MoveVector = sf::Vector2f(0.f, 0.f);
    sf::Vector2f m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    float m_zoom = 1.f;
	sf::Vector2f m_ScreenShake = sf::Vector2f(0.f, 0.f);
};