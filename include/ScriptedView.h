#pragma once

#include "IView.h"

class ScriptedView : public IView
{
public:
    ScriptedView(sf::Vector2f start_pos, sf::Vector2f end_pos, float duration);
    ~ScriptedView();
    void Update();
    void Draw(sf::RenderWindow* window);
private:
    
};