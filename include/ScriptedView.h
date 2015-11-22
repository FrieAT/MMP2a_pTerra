#pragma once

#include "IView.h"

#include "IViewObserver.h"

class ScriptedView : public IView, public IViewObserver
{
public:
    ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed);
    ~ScriptedView();
    void OnEventUpdate(sf::Time delta_time);
    void OnEventDraw(sf::RenderWindow* window);
private:
    sf::Vector2f m_MoveVector;
    sf::Vector2f m_CurrentMovePosition;
    float m_fSteps;
    float m_fSpeed;
    sf::View* m_pView;
    sf::Clock clock;
    void Initialize();
};