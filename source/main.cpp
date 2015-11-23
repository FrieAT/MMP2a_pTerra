#include <iostream>
#include <memory>

#include "Game.h"

#include "GameStateIntro.h"
#include "GameStatePlay.h"

int main(int argc, char const** argv)
{
    // Initialisiere die "Game Engine"
    Game* game_engine = new Game();
    
    // Initialisiere Intro
    game_engine->ChangeState(new GameStateIntro());
    game_engine->Start();
    
    // Lösche alle verbundenen Ressourcen
    delete game_engine;
    
    return EXIT_SUCCESS;
}
