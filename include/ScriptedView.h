#pragma once

#include "IView.h"

class ScriptedView : public IView
{
public:
    ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed);
    ~ScriptedView();
    void Update();
    void Draw(sf::RenderWindow* window);
private:
    sf::Vector2f m_MoveVector;
    float m_fSteps;
    float m_fSpeed;
    sf::View* m_pView;
    sf::Clock clock;
    void Initialize();
};