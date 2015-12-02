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
    void OnFrameUpdate(sf::Time DeltaTime);
    void OnFrameDraw(sf::RenderWindow* pWindow);
    
    sf::FloatRect GetViewport();
private:
    sf::Vector2f m_MoveVector;
    sf::Vector2f m_CurrentMovePosition;
    float m_fSteps;
    float m_fSpeed;
    sf::View* m_pView;
    sf::Clock m_Clock;
};