#pragma once

class IGameState
{
public:
    IGameState() { }
    virtual ~IGameState() { }
    
    // virtual void Pause() = 0; // TODO: Implementation
    // virtual void Resume() = 0; // TODO: Implementation
    
    virtual void Update(sf::RenderWindow* window) = 0;
    
    /*void ChangeState(IGameState* state) {
        Game::ChangeState(state);
    }*/
};