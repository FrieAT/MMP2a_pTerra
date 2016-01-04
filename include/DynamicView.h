/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IView.h"

#include "IFrameObserver.h"

class DynamicView : public IView, public IFrameObserver
{
public:
    DynamicView(sf::FloatRect ViewSize, sf::Vector2f MoveVector, float fSpeed);
    ~DynamicView();
    void Init();
    void OnFrameUpdate(sf::Time DeltaTime);
    void OnFrameDraw(sf::RenderWindow* pWindow);
    void Serialize(SerializeNode* pParentNode);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("DynamicView"); }
    
    sf::FloatRect GetViewport();
private:
    sf::Vector2f m_MoveVector;
    sf::Vector2f m_CurrentMovePosition;
    float m_zoom;
    float m_fSpeed;
    sf::View* m_pView;
};