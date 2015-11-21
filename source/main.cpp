#include <iostream>
#include <memory>

#include "Game.h"

#include "GameStateIntro.h"
#include "GameStatePlay.h"

#include "InputManager.h"

int main(int argc, char const** argv)
{
    // Initialisiere die "Game Engine"
    Game* game_engine = new Game();
    
    // Initialisiere Intro
    game_engine->ChangeState(new GameStateIntro());
    game_engine->Start();
    
    // Initialisiere Spiel
    game_engine->ChangeState(new GameStatePlay());
    
    // Total unnötig, aber zum Testen vom Memory Management.
    game_engine->ChangeState(new GameStatePlay());
    game_engine->ChangeState(new GameStatePlay());
    game_engine->ChangeState(new GameStatePlay());
    
    // Starte die Engine mit dem gesetzten State
    game_engine->Start();
    
    // Lösche alle verbundenen Ressourcen
    delete game_engine;
    
    return EXIT_SUCCESS;
}
