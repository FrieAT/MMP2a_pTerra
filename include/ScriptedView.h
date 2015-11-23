#pragma once

#include "IView.h"

#include "IFrameObserver.h"

class ScriptedView : public IView, public IFrameObserver
{
public:
    ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed);
    ~ScriptedView();
    void OnFrameUpdate(sf::Time delta_time);
    void OnFrameDraw(sf::RenderWindow* window);
    
    sf::FloatRect GetViewport();
private:
    sf::Vector2f m_MoveVector;
    sf::Vector2f m_CurrentMovePosition;
    float m_fSteps;
    float m_fSpeed;
    sf::View* m_pView;
    sf::Clock clock;
    void Initialize();
};